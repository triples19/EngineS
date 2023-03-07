#pragma once

#include "Reflection/FieldInfo.hpp"
#include "Reflection/MemberInfo.hpp"
#include "Reflection/MethodInfo.hpp"

#include <string>
#include <vector>

namespace EngineS {

class Type;
namespace Detail {
struct BaseInfo;
}

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

} // namespace Registration

} // namespace EngineS

#include "Reflection/Impl/Registration.inl"