#pragma once

#include "Core/Concepts.hpp"
#include "Instance.hpp"
#include "MemberInfo.hpp"
#include "TypeOf.hpp"
#include "Variant.hpp"

namespace EngineS {

class Type;

class FieldInfo : public MemberInfo {
  public:
    using MemberInfo::MemberInfo;

    bool                IsStatic() const override = 0;
    virtual const Type* GetType() const           = 0;

    virtual Variant GetValue(Instance instance) const = 0;
    template<class T>
    T GetValue(Instance instance) const {
        return GetValue(instance).GetValue<T>();
    }

    virtual void SetValue(Instance instance, Variant val) const = 0;
};

namespace Detail {

template<class Ptr>
class FieldInfoImpl : public FieldInfo {
  public:
    FieldInfoImpl(std::string_view name, Ptr ptr, AccessLevel accessLevel = AccessLevel::Public) :
        FieldInfo(name, accessLevel), _ptr(ptr) {}

    bool IsStatic() const override { return MemberTrait<Ptr>::IsStatic; }

    const Type* GetType() const override { return TypeOf<typename MemberTrait<Ptr>::Type>(); }

    virtual Variant GetValue(Instance instance) const override {
        if constexpr (MemberTrait<Ptr>::IsStatic) {
            return *_ptr;
        } else {
            auto p = instance.TryConvert<typename MemberTrait<Ptr>::ParentType>();
            return p->*_ptr;
        }
    }

    void SetValue(Instance instance, Variant val) const override {
        if constexpr (MemberTrait<Ptr>::IsStatic) {
            *_ptr = val.GetValue<typename MemberTrait<Ptr>::Type>();
        } else {
            auto p   = instance.TryConvert<typename MemberTrait<Ptr>::ParentType>();
            p->*_ptr = val.GetValue<typename MemberTrait<Ptr>::Type>();
        }
    }

  private:
    Ptr _ptr;
};

} // namespace Detail

} // namespace EngineS
