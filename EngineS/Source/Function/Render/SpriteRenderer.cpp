#include "SpriteRenderer.hpp"

#include "Core/Math/MathHeaders.hpp"
#include "Function/Object/Component/Transform2D.hpp"
#include "Function/Render/Program.hpp"
#include "Function/Render/Texture2D.hpp"

namespace EngineS {

unsigned int SpriteRenderer::_vao = 0;

static float quadVertices[] = {0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
							   0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f};

SpriteRenderer::SpriteRenderer(std::shared_ptr<Program> shader, std::shared_ptr<Texture2D> texture) :
	_program {shader}, _texture {texture} {}

void SpriteRenderer::Render() {
	_program->Use();
	auto	  scale		  = Scale(_texture->width, _texture->height, 1);
	auto	  anchorTrans = Translate(-_anchor.x, -_anchor.y, 0);
	Matrix4x4 modelMat	  = transform->MakeModelMatrix() * scale * anchorTrans;

	_program->Set("model", modelMat);
	_program->Set("spriteColor", _color);

	glActiveTexture(GL_TEXTURE0);
	_texture->Bind();

	glBindVertexArray(_vao);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}

void SpriteRenderer::Initialize(GameObject* parent) {
	Renderer::Initialize(parent);
	if (_vao != 0)
		return;
	unsigned int vbo;
	glGenVertexArrays(1, &_vao);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);
	glBindVertexArray(_vao);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), nullptr);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

} // namespace EngineS