#pragma once

#include "Core/Concepts.hpp"
#include "Ref.hpp"

#include <utility>

namespace EngineS {

template<class T>
class SharedPtr {
  public:
    SharedPtr() : _ptr(nullptr) {}
    SharedPtr(std::nullptr_t) : _ptr(nullptr) {}

    template<DerivedFrom<T> U>
    SharedPtr(const SharedPtr<U>& rhs) : _ptr(rhs._ptr) {
        Retain();
    }

    template<DerivedFrom<T> U>
    SharedPtr(SharedPtr<U>&& rhs) : _ptr(rhs._ptr) {
        rhs._ptr = nullptr;
    }

    SharedPtr(T* ptr) : _ptr(ptr) { Retain(); }

    ~SharedPtr() { Release(); }

    template<DerivedFrom<T> U>
    SharedPtr<T>& operator=(const SharedPtr<U>& rhs) {
        if (_ptr == rhs._ptr)
            return *this;
        SharedPtr<T> copy(rhs);
        Swap(copy);
        return *this;
    }

    template<DerivedFrom<T> U>
    SharedPtr<T>& operator=(SharedPtr<U>&& rhs) {
        SharedPtr<T> copy(std::move(rhs));
        Swap(copy);
        return *this;
    }

    SharedPtr<T>& operator=(T* ptr) {
        if (_ptr == ptr)
            return *this;
        SharedPtr<T> copy(ptr);
        Swap(copy);
        return *this;
    }

    T* operator->() const { return _ptr; }
    T& operator*() const { return *_ptr; }
    T& operator[](int i) { return _ptr[i]; }
    T* Get() const { return _ptr; }

    operator bool() const { return _ptr != nullptr; }

    template<DerivedFrom<T> U>
    bool operator<=>(const SharedPtr<U>& rhs) const {
        return _ptr <=> rhs._ptr;
    }

    void Swap(SharedPtr<T>& rhs) { std::swap(_ptr, rhs._ptr); }

  private:
    void Retain() {
        if (_ptr)
            _ptr->Retain();
    }

    void Release() {
        if (_ptr) {
            _ptr->Release();
            _ptr = nullptr;
        }
    }

  private:
    T* _ptr;
};

} // namespace EngineS