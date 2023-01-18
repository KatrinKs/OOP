#pragma once

#include <iostream>
#include <algorithm>
#include <cassert>
#include <iterator>


template<typename Type>
using value_type = std::conditional_t<std::is_array_v<Type>, std::remove_all_extents_t<Type>, Type>;

template<typename Type>
using pointer = std::add_pointer_t<value_type<Type>>;

template<typename Type>
using reference = std::add_lvalue_reference_t<value_type<Type>>;

template<class Type, class TDeleter = std::default_delete<Type>>
class UniquePTR
{
private: // Disable copy from lvalue.
    using value_type = value_type<Type>;
    using pointer = pointer<Type>;
    using reference = reference<Type>;
     
    pointer u_ptr = nullptr;
    TDeleter deleter;

    friend std::ostream& operator<<(std::ostream& os, const UniquePTR<Type, TDeleter>& up)
    {
        return os << up.get();
    }

public: // Constructors and destructor.    
    constexpr UniquePTR() noexcept requires (std::is_default_constructible_v<TDeleter>): deleter() {};

    explicit UniquePTR(pointer u_ptr_) noexcept requires std::is_default_constructible_v<TDeleter>: u_ptr(u_ptr_), deleter() {};

    explicit UniquePTR(pointer u_ptr_, const TDeleter& del) noexcept : u_ptr(u_ptr_), deleter(del) {};

    UniquePTR(UniquePTR<Type, TDeleter>&& u_ptr_) noexcept // Move constructor.
        : u_ptr(u_ptr_.u_ptr)
    {
        u_ptr_.u_ptr = nullptr;
    }

    ~UniquePTR()
    {
        reset();
    }

public: // Assignment.
    UniquePTR& operator=(UniquePTR&& u_ptr_) noexcept
    {
        reset(u_ptr_.release());
        get_deleter() = std::forward<TDeleter>(u_ptr_.get_deleter());
        return *this;
    }

    UniquePTR& operator=(pointer u_ptr_)
    {
        reset(u_ptr_);
        return *this;
    }
public: // Observers.
    reference operator*() const noexcept // Dereference the stored pointer.
    {
        return *get();
    }

    pointer operator->() const noexcept // Return the stored pointer.
    {
        return get();
    }

    pointer get() const noexcept// Return the stored pointer.
    {
        return u_ptr;
    }

    TDeleter& get_deleter() noexcept // Return a reference to the stored deleter.
    {
        return deleter;
    }

    explicit operator bool() const noexcept // Return false if the stored pointer is null.
    {
        return get() != nullptr;
    }

public: // Modifiers.
    pointer release() noexcept // Release ownership of any stored pointer.
    {
        pointer tmp = get();
        u_ptr = nullptr;
        return tmp;
    }

    void reset(pointer u_ptr_ = nullptr) noexcept // Replace the stored pointer.
    { 
        if (u_ptr == u_ptr_)
        {
            return;
        }
        if (u_ptr)
        {
            get_deleter()(u_ptr);
        }
        u_ptr = u_ptr_;
    }

    reference operator[] (std::size_t index)
    {
        return get()[index];
    }

    void swap(UniquePTR<Type, TDeleter>& u_ptr_) noexcept // Exchange the pointer with another object.
    {
        std::swap(u_ptr, u_ptr_.u_ptr);
    }

    UniquePTR(const UniquePTR<Type, TDeleter>&) = delete;

    UniquePTR<Type, TDeleter>& operator=(const UniquePTR<Type, TDeleter>&) = delete;
};

template<typename T1, typename D1, typename T2, typename D2>
bool operator==(const UniquePTR<T1, D1>& u_ptr_1, const UniquePTR<T2, D2>& u_ptr_2) noexcept
{
    return u_ptr_1.get() == u_ptr_2.get();
}

template<typename T1, typename D1, typename T2, typename D2>
bool operator!=(const UniquePTR<T1, D1>& u_ptr_1, const UniquePTR<T2, D2>& u_ptr_2) noexcept
{
    return !(u_ptr_1 == u_ptr_2);
}
