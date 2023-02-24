#pragma once

#include "Base/PrimitiveTypes.hpp"

#include <string>

namespace EngineS {

enum class AccessLevel : u32 {
    Public,
    Private,
    Protected,
};

class Type;

class MemberInfo {
  public:
    MemberInfo(std::string_view name, AccessLevel accessLevel) : _name(name), _accLevel(accessLevel) {}

    std::string_view GetName() const { return _name; }
    AccessLevel      GetAccessLevel() const { return _accLevel; }
    virtual bool     IsStatic() const = 0;

  private:
    std::string_view _name;
    AccessLevel      _accLevel;
};

namespace Detail {

template<typename>
struct MemberTrait;

template<typename MemberTypeT>
struct MemberTrait<MemberTypeT*> {
    using Type              = MemberTypeT;
    using MemberPointerType = MemberTypeT;

    static constexpr bool IsStatic = true;
};

template<typename ParentTypeT, typename MemberTypeT>
struct MemberTrait<MemberTypeT ParentTypeT::*> {
    using Type              = MemberTypeT;
    using MemberPointerType = MemberTypeT ParentTypeT::*;
    using ParentType        = ParentTypeT;

    static constexpr bool IsStatic = false;
};

template<typename ParentTypeT, typename MemberTypeT>
struct MemberTrait<MemberTypeT ParentTypeT::* const> {
    using Type              = MemberTypeT;
    using MemberPointerType = MemberTypeT ParentTypeT::*;
    using ParentType        = ParentTypeT;

    static constexpr bool IsStatic = false;
};

} // namespace Detail

} // namespace EngineS
