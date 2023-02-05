#pragma once

#include "Base/Variant.hpp"
#include "Reflection/MemberInfo.hpp"
#include "Reflection/TypeOf.hpp"

#include <optional>
#include <tuple>
#include <vector>

namespace EngineS {

class Type;

namespace Detail {
template<class>
class MethodInfoImpl;
}

class ParameterInfo {
    template<class>
    friend class Detail::MethodInfoImpl;

  public:
    ParameterInfo(std::string_view name, std::optional<Variant> defaultValue = std::nullopt) :
        _name(name), _defaultValue(defaultValue) {}

    std::string_view GetName() const { return _name; }
    const Type*      GetType() const { return _type; }
    bool             HasDefaultValue() const { return _defaultValue.has_value(); }
    Variant          GetDefaultValue() const { return _defaultValue.value(); }

  private:
    std::string_view       _name;
    const Type*            _type;
    std::optional<Variant> _defaultValue;
};

class MethodInfo : public MemberInfo {
  public:
    using MemberInfo::MemberInfo;

    bool                                      IsStatic() const override = 0;
    virtual const Type*                       GetReturnType() const     = 0;
    virtual u32                               GetParameterCount() const = 0;
    virtual const std::vector<ParameterInfo>& GetParameterInfos() const = 0;

    virtual Variant Invoke(Object* obj) const = 0;

    virtual Variant Invoke(Object* obj, Variant arg0) const = 0;

    virtual Variant Invoke(Object* obj, Variant arg0, Variant arg1) const = 0;

    virtual Variant Invoke(Object* obj, Variant arg0, Variant arg1, Variant arg2) const = 0;

    virtual Variant Invoke(Object* obj, Variant arg0, Variant arg1, Variant arg2, Variant arg3) const = 0;

    virtual Variant Invoke(Object* obj, Variant arg0, Variant arg1, Variant arg2, Variant arg3, Variant arg4) const = 0;

    virtual Variant
    Invoke(Object* obj, Variant arg0, Variant arg1, Variant arg2, Variant arg3, Variant arg4, Variant arg5) const = 0;
};

namespace Detail {

template<class>
struct SignatureTrait;

template<class Ret, class... Params>
struct SignatureTrait<Ret(Params...)> {
    using ReturnType                  = Ret;
    static constexpr auto ParamsCount = sizeof...(Params);

    static inline std::array<const Type*, ParamsCount> GetParamTypes() { return {TypeOf<Params>()...}; }

    template<size_t Index>
    struct TypeOfParam {
        using Type = std::tuple_element<Index, std::tuple<Params...>>::type;
    };
};

template<class Ptr>
class MethodInfoImpl : public MethodInfo {
  public:
    using MethodType                  = MemberTrait<Ptr>::Type;
    using ReturnType                  = SignatureTrait<MethodType>::ReturnType;
    constexpr static auto ParamsCount = SignatureTrait<MethodType>::ParamsCount;
    template<size_t Index>
    using TypeOfParam = typename SignatureTrait<MethodType>::template TypeOfParam<Index>::Type;

    MethodInfoImpl(
        std::string_view                  name,
        Ptr                               ptr,
        const std::vector<ParameterInfo>& params,
        AccessLevel                       accessLevel = AccessLevel::Public
    ) :
        MethodInfo(name, accessLevel),
        _ptr(ptr), _params(params) {
        ES_ASSERT_NOMSG(params.size() == ParamsCount);
        auto types = SignatureTrait<MethodType>::GetParamTypes();
        for (int i = 0; i < ParamsCount; i++) {
            _params[i]._type = types[i];
        }
    }

    bool IsStatic() const override { return MemberTrait<Ptr>::IsStatic; }

    const Type* GetReturnType() const override { return TypeOf<ReturnType>(); }

    u32 GetParameterCount() const override { return ParamsCount; }

    const std::vector<ParameterInfo>& GetParameterInfos() const override { return _params; }

    Variant Invoke(Object* obj) const override { return InvokeTemplate(obj); }

    Variant Invoke(Object* obj, Variant arg0) const override {
        return InvokeTemplate(obj, static_cast<TypeOfParam<0>>(arg0));
    }

    Variant Invoke(Object* obj, Variant arg0, Variant arg1) const override { return InvokeTemplate(obj, arg0, arg1); }

    Variant Invoke(Object* obj, Variant arg0, Variant arg1, Variant arg2) const override {
        return InvokeTemplate(obj, arg0, arg1, arg2);
    }

    Variant Invoke(Object* obj, Variant arg0, Variant arg1, Variant arg2, Variant arg3) const override {
        return InvokeTemplate(obj, arg0, arg1, arg2, arg3);
    }

    Variant Invoke(Object* obj, Variant arg0, Variant arg1, Variant arg2, Variant arg3, Variant arg4) const override {
        return InvokeTemplate(obj, arg0, arg1, arg2, arg3, arg4);
    }

    Variant Invoke(Object* obj, Variant arg0, Variant arg1, Variant arg2, Variant arg3, Variant arg4, Variant arg5)
        const override {
        return InvokeTemplate(obj, arg0, arg1, arg2, arg3, arg4, arg5);
    }

  private:
    Variant GetDefaultParam(size_t index) const { return _params[index]._defaultValue.value_or(Variant {}); }

    size_t GetNumOfRequiredArgs() const {
        return std::ranges::find_if(_params, [](const ParameterInfo& info) { return info.HasDefaultValue(); }) -
               _params.begin();
    }

    template<class... Args>
    Variant InvokeInternal(Object* obj, Args&&... args) const {
        if constexpr (MemberTrait<Ptr>::IsStatic) {
            if constexpr (SameAs<ReturnType, void>) {
                std::invoke(_ptr, std::forward<Args>(args)...);
                return {};
            } else {
                std::invoke(_ptr, std::forward<Args>(args)...);
            }
        } else {
            if constexpr (SameAs<ReturnType, void>) {
                std::invoke(
                    _ptr,
                    static_cast<typename MemberTrait<Ptr>::ParentType*>(obj),
                    std::forward<Args>(args)...
                );
                return {};
            } else {
                return std::invoke(
                    _ptr,
                    static_cast<typename MemberTrait<Ptr>::ParentType*>(obj),
                    std::forward<Args>(args)...
                );
            }
        }
    }

    template<class... Args, size_t... ProvidedN, size_t... DefaultN>
    Variant
    InvokeHelper(std::index_sequence<ProvidedN...>, std::index_sequence<DefaultN...>, Object* obj, Args&&... args)
        const {
        if (sizeof...(ProvidedN) < GetNumOfRequiredArgs() || sizeof...(ProvidedN) > ParamsCount) {
            // Number of arguments invaild
            return {};
        }
        if (((TypeOf<TypeOfParam<ProvidedN>>() != TypeOf(args)) || ...)) {
            // Types do not match
            return {};
        }
        return InvokeInternal(
            obj,
            static_cast<TypeOfParam<ProvidedN>>(args)..., // Provided arguments
            static_cast<TypeOfParam<sizeof...(ProvidedN) + DefaultN>>(GetDefaultParam(sizeof...(ProvidedN) + DefaultN)
            )... // Default arguments
        );
    }

    template<class... Args>
    Variant InvokeTemplate(Object* obj, Args&&... args) const {
        if constexpr (ParamsCount < sizeof...(Args)) {
            // too many arguments
            return {};
        } else {
            return InvokeHelper(
                std::make_index_sequence<sizeof...(Args)>(),
                std::make_index_sequence<ParamsCount - sizeof...(Args)>(),
                obj,
                std::forward<Args>(args)...
            );
        }
    }

  private:
    Ptr                        _ptr;
    std::vector<ParameterInfo> _params;
};

} // namespace Detail

} // namespace EngineS
