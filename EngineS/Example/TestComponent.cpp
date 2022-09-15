#include "TestComponent.hpp"

void TestComponent::Update(float deltaTime) {
	transform->rotation = transform->rotation + deltaTime * 30.0f;
	if (transform->rotation > 360.0f)
		transform->rotation = 0.0f;
}