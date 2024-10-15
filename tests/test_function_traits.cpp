#include <fsi/function_traits.hpp>

#include <gtest/gtest.h>

using namespace ::testing;

namespace {

template <typename ... Ts>
consteval std::string_view pretty_print()
{
    if constexpr (sizeof...(Ts) == 1)
        return fsi::detail::get_typename<Ts...>();
    else
        return fsi::detail::get_typenames<Ts...>();
}

template <typename Signature, typename ReturnT, typename ... Args>
constexpr void verify_function_signature()
{
    using traits_t = fsi::detail::function_traits<Signature>;

    EXPECT_TRUE((std::is_same_v<typename traits_t::return_t, ReturnT>))
        << "Return types are not the same for \"" << pretty_print<Signature>() << "\""
        << "\n  Expected: " << pretty_print<ReturnT>()
        << "\n  Got: " << pretty_print<typename traits_t::return_t>();

    EXPECT_EQ(sizeof...(Args), traits_t::arity)
        << "Arity is not the same for \"" << pretty_print<Signature>() << "\"";

    if constexpr (sizeof...(Args) != 0)
    {
        constexpr auto compare_args = [] <typename TraitsT, typename ... ExpectedTs, size_t ... Is>(std::index_sequence<Is...>) {
            constexpr bool match = (std::is_same_v<typename TraitsT::at_args_t<Is>, ExpectedTs> && ...);
            EXPECT_TRUE(match)
                << "Parameter types are not the same for \"" << pretty_print<Signature>() << "\""
                << "\n  Expected: " << pretty_print<ExpectedTs...>()
                << "\n  Got: " << pretty_print<typename TraitsT::at_args_t<Is>...>();
        };
        compare_args.template operator()<traits_t, Args...>(std::index_sequence_for<Args...>{});
    }
    else
    {
        EXPECT_TRUE((std::is_same_v<typename traits_t::at_args_t<0>, fsi::detail::typelist_err_t>))
            << "Parameter types are not the same for \"" << pretty_print<Signature>() << "\""
            << "\n  Expected 0 arguments";
    }
}

} // anonymous namespace

TEST(test_function_traits, test_plain_old_function)
{
    verify_function_signature<void(int, int), void, int, int>();
    verify_function_signature<char(std::string_view), char, std::string_view>();
    verify_function_signature<void(), void>();
}
