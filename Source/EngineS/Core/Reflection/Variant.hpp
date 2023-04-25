#pragma once

#include "Core/Concepts.hpp"
#include "Core/TypeTraits.hpp"
#include "TypeOf.hpp"

#include <memory>
#include <unordered_map>
#include <vector>

namespace EngineS {

class Type;
class Variant;

using VariantVector = std::vector<Variant>;
using VariantMap    = std::unordered_map<hash32, Variant>;

namespace Detail {

union VariantData {
    unsigned char data[8];
    void*         ptr;

    VariantData() = default;

    template<class T>
    VariantData(T* p) {
        ptr = static_cast<void*>(p);
    }
};

struct VariantTypeHandler {
    virtual ~VariantTypeHandler()                            = default;
    virtual const Type* GetType() const                      = 0;
    virtual VariantData Create(const void* val) const        = 0;
    virtual VariantData Copy(VariantData other) const        = 0;
    virtual void        Destroy(VariantData obj) const       = 0;
    virtual void*       GetAddress(VariantData obj) const    = 0;
    virtual void*       GetRawAddress(VariantData obj) const = 0;
    virtual bool        IsValid() const                      = 0;

    virtual std::unique_ptr<VariantTypeHandler> Clone() const = 0;
};

} // namespace Detail

class Variant {
  public:
    Variant();
    ~Variant();

    template<class T>
        requires NotSameAs<T, Variant>
    Variant(const T& val);

    Variant(const Variant& other);

    Variant(Variant&& other) noexcept;

    template<class T>
    Variant& operator=(T&& val);

    Variant& operator=(const Variant& other);

    Variant& operator=(Variant&& other) noexcept;

    template<class T>
    operator T() const;

    bool IsValid() const;

    template<class T>
    bool IsType() const;

    template<class T>
    T& GetValue();

    template<class T>
    const T& GetValue() const;

    template<class T>
    T Convert() const;

    template<class T>
    bool operator==(T&& val) const;

    Detail::VariantTypeHandler* GetHandler() const;

    void* GetAddress() const;

    void* GetRawAddress() const;

    const Type* GetType() const;

    int GetInt() const;

    float GetFloat() const;

    double GetDouble() const;

  private:
    template<class T>
    inline T* UnsafeCast();

    template<class T>
    inline const T* UnsafeCast() const;

    template<class T>
    T ToNumber() const;

  private:
    Detail::VariantData                         _data {};
    std::unique_ptr<Detail::VariantTypeHandler> _handler;
};

} // namespace EngineS

#include "Core/Reflection/Impl/Variant.inl"