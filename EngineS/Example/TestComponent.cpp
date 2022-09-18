#include "TestComponent.hpp"

void TestComponent::Update(float deltaTime) {
	transform->SetLocalRotation(transform->GetLocalRotation() + deltaTime * 30.0f);
}