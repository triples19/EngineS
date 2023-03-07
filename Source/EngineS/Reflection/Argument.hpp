#pragma once

namespace EngineS {

class Variant;
class Type;

class Argument {
  public:
    Argument();

    Argument(Argument&& other) noexcept;
    Argument(const Argument& other);

    Argument(Variant& variant);
    Argument(const Variant& variant);

    template<class T>
    Argument(T& val);

    template<class T>
    Argument(const T& val);

    const Type* GetType() const;

    template<class T>
    decltype(auto) GetValue() const;

  private:
    const void* _ptr;
    const Type* _type;
};

} // namespace EngineS

#include "Reflection/Impl/Argument.inl"