#include <fsi/type_erasure.hpp>

#include <gtest/gtest.h>

using namespace ::testing;

FSI_TYPE_ERASURE_MEMBER(push_back)
FSI_TYPE_ERASURE_MEMBER(func)

TEST(test_type_erasure, test_simple)
{
    struct foo {};
    struct goo
    {
        void push_back(int);
        std::string func(int, char, float);
    };


    static_assert(fsi::has_push_back_v<goo, void(int)>);
    static_assert(!fsi::has_push_back_v<foo, void(int)>);

    static_assert(fsi::has_func_v<goo, std::string(int, char, float)>);
    static_assert(!fsi::has_func_v<goo, void(int, char, float)>);
    static_assert(!fsi::has_func_v<goo, std::string(int)>);
}
