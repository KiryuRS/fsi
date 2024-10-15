#pragma once

#include <type_traits>
#include <source_location>
#include <string_view>

namespace fsi::detail {

namespace inner {

template <typename T>
consteval const char* function_name()
{
    return std::source_location::current().function_name();
}

template <typename ... Ts>
consteval const char* function_name_arity()
{
    return std::source_location::current().function_name();
}

} // namespace inner

template <typename T>
consteval std::string_view get_typename()
{
    constexpr auto prefix_location = std::string_view{inner::function_name<void>()}.find("void");
    static_assert(prefix_location != std::string_view::npos, "failed to find prefix location. something is wrong?");

    constexpr auto typename_str = std::string_view{inner::function_name<T>()};
    return typename_str.substr(prefix_location, typename_str.length() - prefix_location - 1);
}

template <typename ... Ts>
consteval std::string_view get_typenames()
{
    constexpr auto prefix_location = std::string_view{inner::function_name_arity<void>()}.find("void");
    static_assert(prefix_location != std::string_view::npos, "failed to find prefix location. something is wrong?");

    constexpr auto typename_str = std::string_view{inner::function_name_arity<Ts...>()};
    return typename_str.substr(prefix_location, typename_str.length() - prefix_location - 2);
}

}
