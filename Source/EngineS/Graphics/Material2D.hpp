#pragma once

#include "Core/Memory/SharedPtr.hpp"
#include "Core/Object.hpp"
#include "Graphics/API/Program.hpp"
#include "Graphics/API/Texture2D.hpp"

#include <memory>

namespace EngineS {

class Program;
class Texture2D;

class Material2D : public Object {
    ES_OBJECT
  public:
    Material2D(Program* program, Texture2D* texture);

    Program*   GetProgram() const { return _program.Get(); }
    Texture2D* GetTexture() const { return _texture.Get(); }

  private:
    SharedPtr<Program>   _program;
    SharedPtr<Texture2D> _texture;
};

} // namespace EngineS
