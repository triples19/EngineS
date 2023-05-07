#pragma once

#include "Core/PrimitiveTypes.hpp"

#include <cstddef>

namespace EngineS {

template<class T>
struct RandomAccessIterator {
    using iterator_category = std::random_access_iterator_tag;
    using difference_type   = i32;
    using value_type        = T;
    using pointer           = T*;
    using reference         = T&;

    constexpr RandomAccessIterator<T>() : ptr(nullptr) {}
    constexpr explicit RandomAccessIterator<T>(T* _ptr) : ptr(_ptr) {}
    constexpr RandomAccessIterator<T>(const RandomAccessIterator& other) : ptr(other.ptr) {}

    constexpr T* operator->() const { return ptr; }
    constexpr T& operator*() const { return *ptr; }

    constexpr RandomAccessIterator<T>& operator++() {
        ++ptr;
        return *this;
    }

    constexpr RandomAccessIterator<T> operator++(int) {
        auto iter = *this;
        ++ptr;
        return iter;
    }

    constexpr RandomAccessIterator<T>& operator--() {
        --ptr;
        return *this;
    }

    constexpr RandomAccessIterator<T> operator--(int) {
        auto iter = *this;
        --ptr;
        return iter;
    }

    constexpr RandomAccessIterator<T>& operator+=(int value) {
        ptr += value;
        return *this;
    }

    constexpr RandomAccessIterator<T>& operator-=(int value) {
        ptr -= value;
        return *this;
    }

    constexpr RandomAccessIterator<T> operator+(int value) const { return RandomAccessIterator<T>(ptr + value); }
    constexpr RandomAccessIterator<T> operator-(int value) const { return RandomAccessIterator<T>(ptr - value); }

    constexpr int operator-(const RandomAccessIterator& rhs) const {
        return static_cast<difference_type>(ptr - rhs.ptr);
    }

    constexpr bool                 operator==(const RandomAccessIterator<T>& rhs) { return ptr == rhs.ptr; }
    constexpr std::strong_ordering operator<=>(const RandomAccessIterator<T>& rhs) { return ptr <=> rhs.ptr; }

    T* ptr;
};

} // namespace EngineS