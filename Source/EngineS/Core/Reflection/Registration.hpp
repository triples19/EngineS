#pragma once

#include "EnumInfo.hpp"
#include "FieldInfo.hpp"
#include "MemberInfo.hpp"
#include "MethodInfo.hpp"

#include <string>
#include <type_traits>
#include <vector>

namespace EngineS {

class Type;

namespace Registration {

void DoRegistration();

template<class T>
class Class {
  public:
    Class(std::string_view name);

    ~Class();

    template<class... Ts>
    inline Class& Bases();

    template<class Ptr>
    inline Class& Field(std::string_view name, Ptr ptr, AccessLevel accessLevel = AccessLevel::Public);

    template<class Ptr>
    inline Class& Method(
        std::string_view                     name,
        Ptr                                  ptr,
        const std::vector<std::string_view>& params,
        AccessLevel                          accessLevel = AccessLevel::Public
    );

    template<class... Params>
    inline Class&
    Constructor(const std::vector<std::string_view>& params, AccessLevel accessLevel = AccessLevel::Public);

    const Type* Get() const { return _type; }

  private:
    Type* _type;
};

template<class T>
    requires std::is_enum_v<T>
class Enum {
  public:
    Enum(std::string_view name);

    Enum& Value(std::string_view name, T val);

    const EnumInfo* Get() const { return _info; }

  private:
    Detail::EnumInfoImpl<T>* _info;
};

} // namespace Registration

} // namespace EngineS

#include "Core/Reflection/Impl/Registration.inl"