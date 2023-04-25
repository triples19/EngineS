#pragma once

#include "Core/Reflection/Argument.hpp"
#include "Core/Reflection/Instance.hpp"
#include "Core/Reflection/ParameterInfo.hpp"
#include "Core/Reflection/TypeOf.hpp"
#include "Core/Reflection/Variant.hpp"

#include <array>
#include <cassert>

namespace EngineS::Detail {

template<class>
struct SignatureTraitBase;

template<class Ret, class... Params>
struct SignatureTraitBase<Ret(Params...)> {
    using ReturnType                  = Ret;
    static constexpr auto ParamsCount = sizeof...(Params);

    static inline std::array<const Type*, ParamsCount> GetParamTypes() { return {TypeOf<Params>()...}; }

    template<size_t Index>
    struct TypeOfParam {
        using Type = typename std::tuple_element<Index, std::tuple<Params...>>::type;
    };
};

template<class>
struct SignatureTrait;

template<class Ret, class... Params>
struct SignatureTrait<Ret(Params...)> : SignatureTraitBase<Ret(Params...)> {};

template<class Ret, class... Params>
struct SignatureTrait<Ret(Params...) const> : SignatureTraitBase<Ret(Params...)> {};

template<class Ptr>
class MethodInfoImpl : public MethodInfo {
  public:
    using MethodType                  = typename MemberTrait<Ptr>::Type;
    using ReturnType                  = typename SignatureTrait<MethodType>::ReturnType;
    constexpr static auto ParamsCount = SignatureTrait<MethodType>::ParamsCount;

    template<size_t Index>
    using TypeOfParam = typename SignatureTrait<MethodType>::template TypeOfParam<Index>::Type;

    MethodInfoImpl(
        std::string_view                     name,
        Ptr                                  ptr,
        const std::vector<std::string_view>& paramNames,
        AccessLevel                          accessLevel = AccessLevel::Public
    ) :
        MethodInfo(name, accessLevel),
        _ptr(ptr) {
        assert(paramNames.size() == ParamsCount);
        auto types = SignatureTrait<MethodType>::GetParamTypes();
        for (int i = 0; i < ParamsCount; i++) {
            _params.emplace_back(paramNames[i], types[i]);
        }
    }

    bool IsStatic() const override { return MemberTrait<Ptr>::IsStatic; }

    const Type* GetReturnType() const override { return TypeOf<ReturnType>(); }

    u32 GetParameterCount() const override { return ParamsCount; }

    const std::vector<ParameterInfo>& GetParameterInfos() const override { return _params; }

    Variant Invoke(Instance instance) const override { return InvokeTemplate(instance); }

    Variant Invoke(Instance instance, Argument arg0) const override { return InvokeTemplate(instance, arg0); }

    Variant Invoke(Instance instance, Argument arg0, Argument arg1) const override {
        return InvokeTemplate(instance, arg0, arg1);
    }

    Variant Invoke(Instance instance, Argument arg0, Argument arg1, Argument arg2) const override {
        return InvokeTemplate(instance, arg0, arg1, arg2);
    }

    Variant Invoke(Instance instance, Argument arg0, Argument arg1, Argument arg2, Argument arg3) const override {
        return InvokeTemplate(instance, arg0, arg1, arg2, arg3);
    }

    Variant Invoke(Instance instance, Argument arg0, Argument arg1, Argument arg2, Argument arg3, Argument arg4)
        const override {
        return InvokeTemplate(instance, arg0, arg1, arg2, arg3, arg4);
    }

    Variant
    Invoke(Instance instance, Argument arg0, Argument arg1, Argument arg2, Argument arg3, Argument arg4, Argument arg5)
        const override {
        return InvokeTemplate(instance, arg0, arg1, arg2, arg3, arg4, arg5);
    }

    Variant InvokeVariadic(Instance instance, const std::vector<Argument>& args) const override {
        if (args.size() != ParamsCount)
            return {};
        return [&]<size_t... ArgIdx>(std::index_sequence<ArgIdx...>) {
            return InvokeTemplate(instance, args[ArgIdx]...);
        }(std::make_index_sequence<ParamsCount>());
    }

  private:
    template<class... Args, size_t... N>
    decltype(auto) InvokeTemplateExpand(std::index_sequence<N...>, Instance instance, Args&&... args) const {
        if constexpr (MemberTrait<Ptr>::IsStatic) {
            return std::invoke(_ptr, std::forward<Args>(args).template GetValue<TypeOfParam<N>>()...);
        } else {
            return std::invoke(
                _ptr,
                instance.TryConvert<typename MemberTrait<Ptr>::ParentType>(),
                std::forward<Args>(args).template GetValue<TypeOfParam<N>>()...
            );
        }
    }

    template<class... Args>
    Variant InvokeTemplate(Instance instance, Args&&... args) const {
        if constexpr (ParamsCount != sizeof...(Args)) {
            return {};
        } else {
            if constexpr (SameAs<ReturnType, void>) {
                InvokeTemplateExpand(std::make_index_sequence<ParamsCount>(), instance, std::forward<Args>(args)...);
                return {};
            } else {
                return InvokeTemplateExpand(
                    std::make_index_sequence<ParamsCount>(),
                    instance,
                    std::forward<Args>(args)...
                );
            }
        }
    }

  private:
    Ptr                        _ptr;
    std::vector<ParameterInfo> _params;
};

} // namespace EngineS::Detail