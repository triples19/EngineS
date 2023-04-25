#pragma once

#include "MemberInfo.hpp"

#include <functional>
#include <optional>
#include <tuple>
#include <vector>

namespace EngineS {

class Type;
class ParameterInfo;
class Instance;
class Variant;
class Argument;

class MethodInfo : public MemberInfo {
  public:
    using MemberInfo::MemberInfo;

    bool                                      IsStatic() const override = 0;
    virtual const Type*                       GetReturnType() const     = 0;
    virtual u32                               GetParameterCount() const = 0;
    virtual const std::vector<ParameterInfo>& GetParameterInfos() const = 0;

    virtual Variant Invoke(Instance instance) const = 0;

    virtual Variant Invoke(Instance instance, Argument arg0) const = 0;

    virtual Variant Invoke(Instance instance, Argument arg0, Argument arg1) const = 0;

    virtual Variant Invoke(Instance instance, Argument arg0, Argument arg1, Argument arg2) const = 0;

    virtual Variant Invoke(Instance instance, Argument arg0, Argument arg1, Argument arg2, Argument arg3) const = 0;

    virtual Variant
    Invoke(Instance instance, Argument arg0, Argument arg1, Argument arg2, Argument arg3, Argument arg4) const = 0;

    virtual Variant
    Invoke(Instance instance, Argument arg0, Argument arg1, Argument arg2, Argument arg3, Argument arg4, Argument arg5)
        const = 0;

    virtual Variant InvokeVariadic(Instance instance, const std::vector<Argument>& args) const = 0;
};

} // namespace EngineS

#include "Core/Reflection/Impl/MethodInfo.inl"