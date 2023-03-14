#pragma once

#include "Base/PrimitiveTypes.hpp"

#include <vector>

namespace EngineS {

class Variant;
class ParameterInfo;
class Argument;

class ConstructorInfo {
  public:
    virtual ~ConstructorInfo() = default;

    virtual u32                               GetParameterCount() const = 0;
    virtual const std::vector<ParameterInfo>& GetParameterInfos() const = 0;

    virtual Variant Invoke() const = 0;

    virtual Variant Invoke(Argument arg0) const = 0;

    virtual Variant Invoke(Argument arg0, Argument arg1) const = 0;

    virtual Variant Invoke(Argument arg0, Argument arg1, Argument arg2) const = 0;

    virtual Variant Invoke(Argument arg0, Argument arg1, Argument arg2, Argument arg3) const = 0;

    virtual Variant Invoke(Argument arg0, Argument arg1, Argument arg2, Argument arg3, Argument arg4) const = 0;

    virtual Variant
    Invoke(Argument arg0, Argument arg1, Argument arg2, Argument arg3, Argument arg4, Argument arg5) const = 0;

    virtual Variant InvokeVariadic(const std::vector<Argument>& args) const = 0;
};

} // namespace EngineS

#include "Reflection/Impl/ConstructorInfo.inl"