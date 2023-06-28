#pragma once

#include "Core/PrimitiveTypes.hpp"

#include <vector>

namespace EngineS {

class Variant;
class Parameter;
class Argument;

class Constructor {
  public:
    virtual ~Constructor() = default;

    virtual u32                           GetParameterCount() const = 0;
    virtual const std::vector<Parameter>& GetParameterInfos() const = 0;

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

#include "Core/Reflection/Impl/Constructor.inl"