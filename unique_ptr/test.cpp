#include "gtest/gtest.h"
#include "../unique_ptr/unique_ptr.hpp"

#include <stdio.h>
#include <memory>
#include <functional>


class T
{
    int* value;
public:
    T(int* a) : value(a) {}
};

template<typename U>
struct TDeleter
{
    TDeleter() {};
    TDeleter(int* a)
    {
    }

    void operator()(U ptr) const
    {
        delete ptr;
    }

    void operator()(U* ptr) const
    {
        delete ptr;
    }
};

TEST(Deleter, T)
{
    ASSERT_EQ(std::is_default_constructible_v<TDeleter<int>>, true);
    ASSERT_EQ(std::is_trivially_copyable_v<TDeleter<int>>, true);
    int a = 0;
    UniquePTR<int, TDeleter<int>> u_ptr(new int, TDeleter<int>(&a));
    ASSERT_NE(u_ptr.get(), nullptr);
}

TEST(Test, DefaultConstructor) 
{
    UniquePTR<int, TDeleter<int>> u_ptr;
    ASSERT_EQ(u_ptr.get(), nullptr);
}

TEST(Test, Constructor)
{
    UniquePTR<int> u_ptr(new int);
    ASSERT_NE(u_ptr.get(), nullptr);
}

TEST(Test, MoveCostructor) 
{
    UniquePTR<int, TDeleter<int>> u_ptr1(new int);
    ASSERT_NE(u_ptr1.get(), nullptr);
    UniquePTR<int, TDeleter<int>> u_ptr2(std::move(u_ptr1));
    ASSERT_EQ(u_ptr1.get(), nullptr);
    ASSERT_NE(u_ptr2.get(), nullptr);
}

TEST(Test, ReleaseTest) 
{
    UniquePTR<int> u_ptr(new int);
    int* ptr = u_ptr.release();
    ASSERT_EQ(u_ptr.get(), nullptr);
    delete ptr;
}

TEST(Test, ResetTest) 
{
    UniquePTR<int> u_ptr(new int);
    u_ptr.reset();
    ASSERT_EQ(u_ptr.get(), nullptr);
    u_ptr.reset(new int);
    ASSERT_NE(u_ptr.get(), nullptr);
}

TEST(Test, ResetTest1)
{
    int* ptr = new int;
    UniquePTR<int> u_ptr(ptr);
    u_ptr.reset(ptr);
    ASSERT_EQ(u_ptr.get(), ptr);
}

TEST(Test, SwapTest) 
{
    UniquePTR<int> u_ptr1(new int(10));
    UniquePTR<int> u_ptr2(new int(20));
    u_ptr1.swap(u_ptr2);
    ASSERT_EQ(*u_ptr1.get(), 20);
    ASSERT_EQ(*u_ptr2.get(), 10);
}

TEST(Test, MoveAssign) 
{
    UniquePTR<int> u_ptr1(new int);
    UniquePTR<int> u_ptr2(new int);
    u_ptr2 = std::move(u_ptr1);
    ASSERT_EQ(u_ptr1.get(), nullptr);
    ASSERT_NE(u_ptr2.get(), nullptr);
}

TEST(Test, BoolConversion) 
{
    UniquePTR<int> u_ptr1;
    UniquePTR<int> u_ptr2(new int);
    ASSERT_FALSE(u_ptr1);
    ASSERT_TRUE(u_ptr2);
}

TEST(Test, DereferenceOperator) 
{
    UniquePTR<int> u_ptr(new int(10));
    ASSERT_EQ(*u_ptr, 10);
}

TEST(Test, EqualOperator) 
{
    UniquePTR<int> u_ptr1;
    UniquePTR<int> u_ptr2(new int);
    ASSERT_NE(u_ptr1, u_ptr2);
}

TEST(SpecializationForArrays, Constructor) 
{
    UniquePTR<int[], TDeleter<int[]>> u_ptr(new int[10]);
    ASSERT_NE(u_ptr.get(), nullptr);
}

TEST(SpecializationForArrays, MoveCostructor) 
{
    UniquePTR<int[], TDeleter<int[]>> u_ptr1(new int[10]);
    ASSERT_NE(u_ptr1.get(), nullptr);
    UniquePTR<int[], TDeleter<int[]>> u_ptr2(std::move(u_ptr1));
    ASSERT_EQ(u_ptr1.get(), nullptr);
    ASSERT_NE(u_ptr2.get(), nullptr);
}

TEST(SpecializationForArrays, ReleaseTest) 
{
    UniquePTR<int[]> u_ptr(new int[10]);
    int* arr = u_ptr.release();
    ASSERT_EQ(u_ptr.get(), nullptr);
    delete[] arr;
}

TEST(SpecializationForArrays, ResetTest) 
{
    UniquePTR<int[], TDeleter<int[]>> u_ptr(new int[10]);
    u_ptr.reset();
    ASSERT_EQ(u_ptr.get(), nullptr);
    u_ptr.reset(new int[10]);
    ASSERT_NE(u_ptr.get(), nullptr);
}

TEST(SpecializationForArrays, SwapTest)
{
    UniquePTR<int[]> u_ptr1(new int[10]);
    UniquePTR<int[]> u_ptr2;
    u_ptr1.swap(u_ptr2);
    ASSERT_EQ(u_ptr1.get(), nullptr);
    ASSERT_NE(u_ptr2.get(), nullptr);
}

TEST(SpecializationForArrays, MoveAssign) 
{
    UniquePTR<int[]> u_ptr1(new int[10]);
    UniquePTR<int[]> u_ptr2(new int[10]);
    u_ptr2 = std::move(u_ptr1);
    ASSERT_EQ(u_ptr1.get(), nullptr);
    ASSERT_NE(u_ptr2.get(), nullptr);
}

TEST(SpecializationForArrays, BoolConversion) 
{
    UniquePTR<int[]> u_ptr1;
    UniquePTR<int[]> u_ptr2(new int[10]);
    ASSERT_FALSE(u_ptr1);
    ASSERT_TRUE(u_ptr2);
}

TEST(SpecializationForArrays, BracketOperator) 
{
    UniquePTR<int[]> u_ptr(new int[10]);
    for (size_t i = 0; i < 10; i++)
    {
        u_ptr[i] = i * i;
    }
    for (size_t i = 0; i < 10; i++)
        ASSERT_EQ(u_ptr[i], i * i);
}

TEST(SpecializationForArrays, EqualOperator)
{
    UniquePTR<int[]> u_ptr1;
    UniquePTR<int[]> u_ptr2(new int[10]);
    ASSERT_NE(u_ptr1.get(), u_ptr2.get());
}
