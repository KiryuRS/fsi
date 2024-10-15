# Overview

Allow a struct/class of any type to be constructed as long as it matches the function signature conditions.
This achieves type erasure pattern without the use of virtual keywords.  
  
This is a header only library

# Motivation

Inspired from [Boost type erasure (multi function)](https://www.boost.org/doc/libs/1_55_0/doc/html/boost_typeerasure/examples.html#boost_typeerasure.examples.multifunction) and other non C/C++ languages.
In C++, it is extremely difficult to achieve type erasure while maintaining a scalable framework and avoiding virtual functions, since the language itself cannot be type agnostic.
In Boost, this can be achieved by defining the `BOOST_TYPE_ERASURE_MEMBER` and `boost::any` + `boost::mpl::vector`. However, as with Boost, it is a massively library and can be quite heavy in terms of compilation.  
  
See https://stackoverflow.com/questions/76537836/boost-type-erasure-with-multiple-boost-type-erasure-members  

* https://stackoverflow.com/questions/37094710/how-can-i-design-storage-that-conforms-to-the-standards-implementation-of-std/37101152#37101152
* https://github.com/boostorg/any/blob/develop/include/boost/any.hpp

# Incremental Steps

1. Create a concept (not C++20's concept, the traditional SFINAE/metaprogramming way) that returns true if a type has the function signature
2. Create a custom vector that holds 1 or more of such concepts, and accepts any type as long as it satisfies the conditions
3. Create your standard vector functionalities to comply with stl standard library
