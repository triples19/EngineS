#pragma once

#include "Reflection/MemberInfo.hpp"
#include "Reflection/MethodInfo.hpp"

#include <string>

namespace EngineS {

class Type;

namespace Registration {

void DoRegistration();

template<class T>
class Class {
  public:
    Class(std::string_view name, const Type* baseType);

    template<class Ptr>
    Class& Field(std::string_view name, Ptr ptr, AccessLevel accessLevel = AccessLevel::Public);

    template<class Ptr>
    Class& Method(
        std::string_view                  name,
        Ptr                               ptr,
        const std::vector<ParameterInfo>& params,
        AccessLevel                       accessLevel = AccessLevel::Public
    );

    const Type* Get() const { return _type; }

  private:
    Type* _type;
};

} // namespace Registration

} // namespace EngineS

#include "Base/Hash.hpp"
#include "Reflection/FieldInfo.hpp"
#include "Reflection/MethodInfo.hpp"
#include "Reflection/Type.hpp"
#include "Reflection/TypeRegistry.hpp"

namespace EngineS::Registration {

template<class T>
Class<T>::Class(std::string_view name, const Type* baseType) {
    _type = new Detail::TypeImpl<T>(name, baseType);
    TypeRegistry::Instance()->RegisterType(_type);
}

template<class T>
template<class Ptr>
Class<T>& Class<T>::Field(std::string_view name, Ptr ptr, AccessLevel accessLevel) {
    auto hash            = Hasher<std::string_view> {}(name);
    auto info            = new Detail::FieldInfoImpl(name, ptr, accessLevel);
    _type->_fields[hash] = info;
    return *this;
}

template<class T>
template<class Ptr>
Class<T>&
Class<T>::Method(std::string_view name, Ptr ptr, const std::vector<ParameterInfo>& params, AccessLevel accessLevel) {
    auto hash = Hasher<std::string_view> {}(name);
    auto info = new Detail::MethodInfoImpl(name, ptr, params, accessLevel);
    _type->_methods.insert({hash, info});
    return *this;
}

} // namespace EngineS::Registration
