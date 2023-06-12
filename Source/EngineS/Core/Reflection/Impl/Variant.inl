#pragma once

#include "Core/Memory/Ref.hpp"
#include "Core/Reflection/Type.hpp"

#include <algorithm>
#include <iterator>

namespace EngineS {

namespace Detail {

/// Variants containing nothing
struct VariantHandlerEmpty : VariantHandlerBase {
    const Type* GetType() const override {
        return nullptr;
    }
    VariantData Create(const void* val) const override {
        return {};
    }
    VariantData Copy(const VariantData& other) const override {
        return {};
    }
    void  Destroy(VariantData& obj) const override {}
    void* GetRawAddress(const VariantData& obj) const override {
        return nullptr;
    }
    bool IsValid() const override {
        return false;
    }

    std::unique_ptr<VariantHandlerBase> Clone() const override {
        return std::make_unique<VariantHandlerEmpty>();
    }
};

/// Variants storing data on the heap
template<class T>
struct VariantHandlerHeap : VariantHandlerBase {
    const Type* GetType() const override {
        return TypeOf<T>();
    }

    VariantData Create(const void* val) const override {
        return new T(*static_cast<const T*>(val));
    }

    VariantData Copy(const VariantData& other) const override {
        return Create(other.ptr);
    }

    void Destroy(VariantData& obj) const override {
        delete static_cast<T*>(obj.ptr);
    }

    void* GetRawAddress(const VariantData& obj) const override {
        return RawAddressOf(static_cast<const T*>(obj.ptr));
    }

    bool IsValid() const override {
        return true;
    }

    std::unique_ptr<VariantHandlerBase> Clone() const override {
        return std::make_unique<VariantHandlerHeap<T>>();
    }
};

/// Variants storing data on the stack
template<class T>
struct VariantHandlerStack : VariantHandlerBase {
    const Type* GetType() const override {
        return TypeOf<T>();
    }

    VariantData Create(const void* val) const override {
        VariantData ret;
        new (ret.data) T(*static_cast<const T*>(val));
        return ret;
    }

    VariantData Copy(const VariantData& other) const override {
        return Create(other.data);
    }

    void Destroy(VariantData& obj) const override {
        T* ptr = reinterpret_cast<T*>(obj.data);
        ptr->~T();
    }

    void* GetRawAddress(const VariantData& obj) const override {
        return RawAddressOf(reinterpret_cast<const T*>(obj.data));
    }

    bool IsValid() const override {
        return true;
    }

    std::unique_ptr<VariantHandlerBase> Clone() const override {
        return std::make_unique<VariantHandlerStack<T>>();
    }
};

/// Default handler
template<class T>
struct VariantHandler : VariantHandlerHeap<T> {};

/// Specialization for types that fit in 8 bytes
template<class T>
    requires(sizeof(T) <= 8)
struct VariantHandler<T> : VariantHandlerStack<T> {};

template<class T>
    requires DerivedFrom<T, Ref>
struct VariantHandler<T*> : VariantHandlerBase {
    const Type* GetType() const override {
        return TypeOf<T>();
    }

    VariantData Create(const void* val) const override {
        Ref* obj = *const_cast<Ref**>(static_cast<Ref* const*>(val));
        obj->Retain();
        VariantData ret;
        ret.ptr = obj;
        return ret;
    }

    VariantData Copy(const VariantData& other) const override {
        return Create(other.ptr);
    }

    void Destroy(VariantData& obj) const override {
        Ref* ref = const_cast<Ref*>(static_cast<const Ref*>(obj.ptr));
        ref->Release();
    }

    void* GetRawAddress(const VariantData& obj) const override {
        return const_cast<void*>(obj.ptr);
    }

    bool IsValid() const override {
        return true;
    }

    std::unique_ptr<VariantHandlerBase> Clone() const override {
        return std::make_unique<VariantHandler<T*>>();
    }
};

template<class T>
struct VariantHandler<std::vector<T>> : VariantHandlerHeap<std::vector<T>> {
    const Type* GetType() const override {
        return TypeOf<VariantVector>();
    }
    VariantData Create(const void* val) const override {
        return CopyContainer<std::vector<T>, VariantVector>(val);
    }
};

template<>
struct VariantHandler<VariantVector> : VariantHandlerHeap<VariantVector> {
    VariantData Create(const void* val) const override {
        return CopyContainer<VariantVector, VariantVector>(val);
    }
};

template<class T>
struct VariantHandler<std::unordered_map<hash32, T>> : VariantHandlerHeap<std::unordered_map<hash32, T>> {
    const Type* GetType() const override {
        return TypeOf<VariantMap>();
    }
    VariantData Create(const void* val) const override {
        return CopyContainer<std::unordered_map<hash32, T>, VariantMap>(val);
    }
};

template<>
struct VariantHandler<VariantMap> : VariantHandlerHeap<VariantMap> {
    VariantData Create(const void* val) const override {
        return CopyContainer<VariantMap, VariantMap>(val);
    }
};

} // namespace Detail

template<class T>
    requires NotSameAs<T, Variant>
Variant::Variant(const T& val) : _handler(new Detail::VariantHandler<T>) {
    _data = _handler->Create(reinterpret_cast<void*>(const_cast<RemoveCVRef<T*>>(&val)));
}

template<class T>
Variant& Variant::operator=(T&& val) {
    *this = Variant(std::forward<T>(val));
    return *this;
}

template<class T>
Variant::operator T() const {
    return GetValue<T>();
}

template<class T>
bool Variant::IsType() const {
    return TypeOf<T>() == _handler->GetType();
}

template<class T>
T Variant::Convert() const {
    return static_cast<T>(Type::ApplyOffset(TypeOf<T>(), _handler->GetType(), _handler->GetRawAddress(_data)));
}

template<class T>
bool Variant::operator==(T&& val) const {
    if (!_handler || TypeOf(val) != _handler->GetType()) {
        return false;
    }
    return GetValue<RemoveCVRef<T>>() == std::forward<T>(val);
}

template<class T>
T Variant::ToNumber() const {
    if (IsType<int>()) {
        return static_cast<T>(GetValue<int>());
    } else if (IsType<signed char>()) {
        return static_cast<T>(GetValue<signed char>());
    } else if (IsType<unsigned char>()) {
        return static_cast<T>(GetValue<unsigned char>());
    } else if (IsType<short int>()) {
        return static_cast<T>(GetValue<short int>());
    } else if (IsType<unsigned short int>()) {
        return static_cast<T>(GetValue<unsigned short int>());
    } else if (IsType<long int>()) {
        return static_cast<T>(GetValue<long int>());
    } else if (IsType<unsigned long int>()) {
        return static_cast<T>(GetValue<unsigned long int>());
    } else if (IsType<long long int>()) {
        return static_cast<T>(GetValue<long long int>());
    } else if (IsType<unsigned long long int>()) {
        return static_cast<T>(GetValue<unsigned long long int>());
    } else if (IsType<bool>()) {
        return static_cast<T>(GetValue<bool>());
    } else if (IsType<float>()) {
        return static_cast<T>(GetValue<float>());
    } else if (IsType<double>()) {
        return static_cast<T>(GetValue<double>());
    } else if (IsType<long double>()) {
        return static_cast<T>(GetValue<long double>());
    } else {
        return static_cast<T>(0);
    }
}

} // namespace EngineS