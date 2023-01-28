#include "Render/SpriteRenderer.hpp"
#include "Function/Camera.hpp"
#include "Function/GameObject.hpp"
#include "Function/Scene.hpp"
#include "Function/SceneManager.hpp"
#include "Function/Transform2D.hpp"
#include "Math/Math.hpp"
#include "Render/Buffer.hpp"
#include "Render/DrawList.hpp"
#include "Render/Material2D.hpp"
#include "Render/Program.hpp"
#include "Render/RenderDevice.hpp"
#include "Render/RenderPipeline.hpp"
#include "Render/RenderSystem.hpp"
#include "Render/Texture2D.hpp"

namespace EngineS {

SpriteRenderer::SpriteRenderer() {
    auto device   = RenderDevice::Instance();
    _vertexBuffer = device->CreateBuffer(6 * sizeof(V2F_C4F_T2F), BufferType::Vertex, BufferUsage::Dynamic);
    _vertexBuffer->Retain();
}

SpriteRenderer::~SpriteRenderer() {
    _vertexBuffer->Release();
}

void SpriteRenderer::Render(const Matrix4x4& modelMat) {
    auto device = RenderDevice::Instance();
    if (!_material) {
        return;
    }
    auto camera = SceneManager::Instance()->GetCurrentScene()->GetMainCamera();
    auto proj   = camera->GetProjectionMatrix();
    auto view   = camera->GetViewMatrix();

    V2F_C4F_T2F_Quad quad;

    quad.tl.vertices = {0.0f, 1.0f};
    quad.tr.vertices = {1.0f, 1.0f};
    quad.bl.vertices = {0.0f, 0.0f};
    quad.br.vertices = {1.0f, 0.0f};

    quad.tl.colors = _color;
    quad.tr.colors = _color;
    quad.bl.colors = _color;
    quad.br.colors = _color;

    auto doVertexTransform = [&](Vector2& vert) {
        auto    texture         = _material->GetTexture();
        Vector2 vertTransformed = (vert - _anchor) * Vector2(texture->GetWidth(), texture->GetHeight());
        Vector4 vertHomo {vertTransformed.x, vertTransformed.y, 0.0f, 1.0f};
        vertHomo = proj * view * modelMat * vertHomo;
        vert     = {vertHomo.x, vertHomo.y};
    };

    doVertexTransform(quad.tl.vertices);
    doVertexTransform(quad.tr.vertices);
    doVertexTransform(quad.bl.vertices);
    doVertexTransform(quad.br.vertices);

    quad.tl.texCoords = {0.0f, 1.0f};
    quad.tr.texCoords = {1.0f, 1.0f};
    quad.bl.texCoords = {0.0f, 0.0f};
    quad.br.texCoords = {1.0f, 0.0f};

    std::array<V2F_C4F_T2F, 6> buffer = {quad.tl, quad.br, quad.bl, quad.tl, quad.tr, quad.br};

    _vertexBuffer->UpdateData(reinterpret_cast<const byte*>(buffer.data()));

    RenderPipelineDescriptor desc {
        .program = _material->GetProgram(),
        .vertexLayout =
            {.attributes =
                 {VertexAttribute {
                      .location   = 0,
                      .offset     = 0,
                      .format     = VertexFormat::Float2,
                      .normalized = false,
                  },
                  VertexAttribute {
                      .location   = 1,
                      .offset     = sizeof(Vector2),
                      .format     = VertexFormat::Float4,
                      .normalized = false,
                  },
                  VertexAttribute {
                      .location   = 2,
                      .offset     = sizeof(Vector2) + sizeof(Color4F),
                      .format     = VertexFormat::Float2,
                      .normalized = false,
                  }},
             .stride = sizeof(V2F_C4F_T2F)},
        .renderPrimitive    = RenderPrimitive::Triangles,
        .rasterizationState = {},
    };
    auto pipeline = device->CreateRenderPipeline(desc);

    auto dl = device->CreateDrawList();
    dl->Begin();
    dl->BindRenderPipeline(pipeline);
    dl->BindVertexBuffer(_vertexBuffer);
    dl->BindTexture(_material->GetTexture());
    dl->Draw(0, buffer.size());
    dl->End();
}

void SpriteRenderer::Initialize(GameObject* parent) {
    Renderer::Initialize(parent);
}

} // namespace EngineS