#pragma once

#include "Reflection/Type.hpp"

#include <algorithm>
#include <iterator>

namespace EngineS {

namespace Detail {

struct VariantTypeHandlerImplEmpty : VariantTypeHandler {
    const Type* GetType() const override { return nullptr; }
    VariantData Create(const void* val) const override { return {}; }
    VariantData Copy(VariantData other) const override { return {}; }
    void        Destroy(VariantData obj) const override {}
    void*       GetRawPointer(VariantData obj) const override { return nullptr; }
    bool        IsValid() const override { return false; }

    std::unique_ptr<VariantTypeHandler> Clone() const override {
        return std::make_unique<VariantTypeHandlerImplEmpty>();
    }
};

template<class T>
struct VariantTypeHandlerImplHeap : VariantTypeHandler {
    const Type* GetType() const override { return TypeOf<T>(); }
    VariantData Create(const void* val) const override { return new T(*static_cast<const T*>(val)); }
    VariantData Copy(VariantData other) const override { return Create(other.ptr); }
    void        Destroy(VariantData obj) const override { delete static_cast<T*>(obj.ptr); }
    void*       GetRawPointer(VariantData obj) const override {
        auto ptr = static_cast<T*>(obj.ptr);
        return const_cast<void*>(static_cast<const void*>(RawAddressOf(ptr)));
    }
    bool IsValid() const override { return true; }

    std::unique_ptr<VariantTypeHandler> Clone() const override {
        return std::make_unique<VariantTypeHandlerImplHeap<T>>();
    }
};

template<class T>
struct VariantTypeHandlerImpl : VariantTypeHandlerImplHeap<T> {};

template<class T>
struct VariantTypeHandlerImpl<std::vector<T>> : VariantTypeHandlerImplHeap<std::vector<T>> {
    const Type* GetType() const override { return TypeOf<VariantVector>(); }
    VariantData Create(const void* val) const override { return CopyContainer<std::vector<T>, VariantVector>(val); }
};

template<>
struct VariantTypeHandlerImpl<VariantVector> : VariantTypeHandlerImplHeap<VariantVector> {
    VariantData Create(const void* val) const override { return CopyContainer<VariantVector, VariantVector>(val); }
};

template<class T>
struct VariantTypeHandlerImpl<std::unordered_map<hash32, T>>
    : VariantTypeHandlerImplHeap<std::unordered_map<hash32, T>> {
    const Type* GetType() const override { return TypeOf<VariantMap>(); }
    VariantData Create(const void* val) const override {
        return CopyContainer<std::unordered_map<hash32, T>, VariantMap>(val);
    }
};

template<>
struct VariantTypeHandlerImpl<VariantMap> : VariantTypeHandlerImplHeap<VariantMap> {
    VariantData Create(const void* val) const override { return CopyContainer<VariantMap, VariantMap>(val); }
};

} // namespace Detail

template<class T>
Variant::Variant(const T& val) : _handler(new Detail::VariantTypeHandlerImpl<T>) {
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
T& Variant::GetValue() {
    return *UnsafeCast<T>();
}

template<class T>
const T& Variant::GetValue() const {
    return *UnsafeCast<T>();
}

template<class T>
T Variant::Convert() const {
    return static_cast<T>(Type::ApplyOffset(TypeOf<T>(), _handler->GetType(), _handler->GetRawPointer(_data)));
}

template<class T>
bool Variant::operator==(T&& val) const {
    if (!_handler || TypeOf(val) != _handler->GetType()) {
        return false;
    }
    return GetValue<RemoveCVRef<T>>() == std::forward<T>(val);
}

template<class T>
T* Variant::UnsafeCast() {
    return reinterpret_cast<T*>(_data.ptr);
}

template<class T>
const T* Variant::UnsafeCast() const {
    return reinterpret_cast<const T*>(_data.ptr);
}

} // namespace EngineS