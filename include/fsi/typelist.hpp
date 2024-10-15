#pragma once

#include <fsi/type_traits.hpp>

namespace fsi::detail {

template <typename ... Ts>
struct typelist
{
};

// dummy class to represent an error type
struct typelist_err_t
{
};

template <size_t N, typename Typelist>
struct at_typelist;

template <size_t N>
struct at_typelist<N, typelist<>>
{
    using type = typelist_err_t;
};

template <typename T, typename ... Ts>
struct at_typelist<0, typelist<T, Ts...>>
{
    using type = T;
};

template <size_t N, typename T, typename ... Ts>
struct at_typelist<N, typelist<T, Ts...>>
{
    using type = at_typelist<N-1, typelist<Ts...>>::type;
};

template <size_t N, typename Typelist>
using at_typelist_t = at_typelist<N, Typelist>::type;

} // namespace fsi::detail
