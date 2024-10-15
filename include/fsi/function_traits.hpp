#pragma once

#include <fsi/typelist.hpp>

namespace fsi::detail {

template <typename Signature>
struct function_traits;

// plain old functions - e.g. void(int, int)
template <typename R, typename ... Args>
struct function_traits<R(Args...)>
{
    using return_t = R;
    static constexpr size_t arity = sizeof...(Args);
    using args_holder_t = typelist<Args...>;

    template <size_t N>
    using at_args_t = at_typelist_t<N, args_holder_t>;
};

} // namespace fsi::detail
