#pragma once

#include <fsi/function_traits.hpp>
#include <utility>

namespace fsi {

#define FSI_TYPE_ERASURE_MEMBER_NAMED(concept_name, member)                                                                                             \
    namespace fsi::detail::inner {                                                                                                                      \
        template <typename Class, typename Signature, typename Sequence, typename = std::void_t<>>                                                      \
        struct concept_name : std::false_type                                                                                                           \
        {                                                                                                                                               \
        };                                                                                                                                              \
                                                                                                                                                        \
        template <typename Class, typename Signature, size_t ... Is>                                                                                    \
        struct concept_name<                                                                                                                            \
            Class,                                                                                                                                      \
            Signature,                                                                                                                                  \
            std::index_sequence<Is...>,                                                                                                                 \
            std::void_t<decltype(std::declval<Class>().member(std::declval<typename detail::function_traits<Signature>::at_args_t<Is>>()...))>          \
        > : std::conditional_t<                                                                                                                         \
                std::is_same_v<decltype(std::declval<Class>().member(std::declval<typename detail::function_traits<Signature>::at_args_t<Is>>()...)),   \
                               typename detail::function_traits<Signature>::return_t>,                                                                  \
                std::true_type,                                                                                                                         \
                std::false_type                                                                                                                         \
            >                                                                                                                                           \
        {                                                                                                                                               \
        };                                                                                                                                              \
    }                                                                                                                                                   \
                                                                                                                                                        \
    namespace fsi {                                                                                                                                     \
        template <typename Class, typename Signature>                                                                                                   \
        struct concept_name : detail::inner::concept_name<Class, Signature, std::make_index_sequence<detail::function_traits<Signature>::arity>>        \
        {                                                                                                                                               \
        };                                                                                                                                              \
                                                                                                                                                        \
        template <typename Class, typename Signature>                                                                                                   \
        static constexpr bool concept_name ## _v = concept_name<Class, Signature>::value;                                                               \
    }

#define FSI_TYPE_ERASURE_MEMBER(member) FSI_TYPE_ERASURE_MEMBER_NAMED(has_##member, member)

// TODO:
// - Create an "any" class that accepts any type as long as it passes the concepts passed in

} // namespace fsi
