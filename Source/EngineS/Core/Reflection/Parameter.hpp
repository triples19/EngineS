#pragma once

#include <string_view>

namespace EngineS {

class Type;

class Parameter {
  public:
    Parameter(std::string_view name, const Type* type) : _name(name), _type(type) {}

    std::string_view GetName() const {
        return _name;
    }
    const Type* GetType() const {
        return _type;
    }

  private:
    std::string_view _name;
    const Type*      _type;
};

} // namespace EngineS
