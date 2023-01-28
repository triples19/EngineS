#pragma once

#include "Math/Math.hpp"
#include "Render/Shader.hpp"
#include "Resource/Resource.hpp"

#include <memory>
#include <optional>
#include <string>

namespace EngineS {

class Program : public Resource {
    ES_OBJECT

  public:
    virtual bool Load(const std::filesystem::path& path) override;
    virtual bool Link(Shader* fragShader, Shader* vertShader) = 0;

    //    void Set(const std::string& name, bool value) const;
    //    void Set(const std::string& name, int value) const;
    //    void Set(const std::string& name, float value) const;
    //    void Set(const std::string& name, const Vector2& value) const;
    //    void Set(const std::string& name, float x, float y) const;
    //    void Set(const std::string& name, const Vector3& value) const;
    //    void Set(const std::string& name, float x, float y, float z) const;
    //    void Set(const std::string& name, const Vector4& value) const;
    //    void Set(const std::string& name, float x, float y, float z, float w);
    //    void Set(const std::string& name, const Matrix3x3& mat) const;
    //    void Set(const std::string& name, const Matrix4x4& mat) const;
};

} // namespace EngineS
