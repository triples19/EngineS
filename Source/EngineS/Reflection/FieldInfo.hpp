#pragma once

#include "Base/Concepts.hpp"
#include "Base/Variant.hpp"
#include "Reflection/MemberInfo.hpp"
#include "Reflection/TypeOf.hpp"

namespace EngineS {

class Type;

class FieldInfo : public MemberInfo {
  public:
    using MemberInfo::MemberInfo;

    bool                IsStatic() const override                = 0;
    virtual const Type* GetType() const                          = 0;
    virtual Variant     GetValue(const Object* obj) const        = 0;
    virtual void        SetValue(Object* obj, Variant val) const = 0;
};

namespace Detail {

template<class Ptr>
class FieldInfoImpl : public FieldInfo {
  public:
    FieldInfoImpl(std::string_view name, Ptr ptr, AccessLevel accessLevel = AccessLevel::Public) :
        FieldInfo(name, accessLevel), _ptr(ptr) {}

    bool IsStatic() const override { return MemberTrait<Ptr>::IsStatic; }

    const Type* GetType() const override { return TypeOf<typename MemberTrait<Ptr>::Type>(); }

    virtual Variant GetValue(const Object* obj) const override {
        // TODO: Handle types that are not convertible from/to Variant
        if constexpr (std::is_convertible_v<typename MemberTrait<Ptr>::Type, Variant>) {
            return dynamic_cast<const typename MemberTrait<Ptr>::ParentType*>(obj)->*_ptr;
        } else {
            return {};
        }
    }

    void SetValue(Object* obj, Variant val) const override {
        // TODO: Handle types that are not convertible from/to Variant
        if constexpr (ExplicitlyConvertibleTo<Variant, typename MemberTrait<Ptr>::Type>) {
            static_cast<typename MemberTrait<Ptr>::ParentType*>(obj)->*_ptr =
                static_cast<typename MemberTrait<Ptr>::Type>(val);
        }
    }

  private:
    Ptr _ptr;
};

} // namespace Detail

} // namespace EngineS
