#pragma once

#include "Core/Reflection/Argument.hpp"
#include "Core/Reflection/MemberInfo.hpp"
#include "Core/Reflection/Parameter.hpp"
#include "Core/Reflection/TypeOf.hpp"
#include "Core/Reflection/Variant.hpp"

#include <cassert>
#include <string_view>
#include <tuple>

namespace EngineS::Detail {

template<class T, class... ParamTypes>
    requires std::constructible_from<T, ParamTypes...>
class ConstructorImpl : public Constructor {
  public:
    using ParamTypesTuple             = std::tuple<ParamTypes...>;
    constexpr static auto ParamsCount = sizeof...(ParamTypes);

    template<size_t Index>
    using TypeOfParam = std::tuple_element_t<Index, ParamTypesTuple>;

    ConstructorImpl(const std::vector<std::string_view>& paramNames, AccessLevel accessLevel = AccessLevel::Public) :
        _accessLevel(accessLevel) {
        assert(paramNames.size() == ParamsCount);
        std::vector<const Type*> paramTypes = {TypeOf<ParamTypes>()...};
        for (int i = 0; i < ParamsCount; i++) {
            _paramInfos.emplace_back(paramNames[i], paramTypes[i]);
        }
    }

    u32 GetParameterCount() const override {
        return ParamsCount;
    }

    const std::vector<Parameter>& GetParameterInfos() const override {
        return _paramInfos;
    }

    Variant Invoke() const override {
        return InvokeTemplate();
    }

    Variant Invoke(Argument arg0) const override {
        return InvokeTemplate(arg0);
    }

    Variant Invoke(Argument arg0, Argument arg1) const override {
        return InvokeTemplate(arg0, arg1);
    }

    Variant Invoke(Argument arg0, Argument arg1, Argument arg2) const override {
        return InvokeTemplate(arg0, arg1, arg2);
    }

    Variant Invoke(Argument arg0, Argument arg1, Argument arg2, Argument arg3) const override {
        return InvokeTemplate(arg0, arg1, arg2, arg3);
    }

    Variant Invoke(Argument arg0, Argument arg1, Argument arg2, Argument arg3, Argument arg4) const override {
        return InvokeTemplate(arg0, arg1, arg2, arg3, arg4);
    }

    Variant
    Invoke(Argument arg0, Argument arg1, Argument arg2, Argument arg3, Argument arg4, Argument arg5) const override {
        return InvokeTemplate(arg0, arg1, arg2, arg3, arg4, arg5);
    }

    Variant InvokeVariadic(const std::vector<Argument>& args) const override {
        if (args.size() != ParamsCount)
            return {};
        return [&]<size_t... ArgIdx>(std::index_sequence<ArgIdx...>) {
            return InvokeTemplate(args[ArgIdx]...);
        }(std::make_index_sequence<ParamsCount>());
    }

  private:
    template<class... Args>
    T* InvokeTemplate(Args&&... args) const {
        if constexpr (sizeof...(Args) != ParamsCount) {
            return nullptr;
        } else {
            return [&]<size_t... ArgIdx>(std::index_sequence<ArgIdx...>) {
                return new T(std::forward<Args>(args).template GetValue<TypeOfParam<ArgIdx>>()...);
            }(std::make_index_sequence<ParamsCount>());
        }
    }

  private:
    std::vector<Parameter> _paramInfos;
    AccessLevel            _accessLevel;
};

} // namespace EngineS::Detail
