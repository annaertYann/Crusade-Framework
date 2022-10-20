#include "UIElement.h"
#include "Camera.h"
#include "Transform.h"
#include "Renderer.h"
using namespace Crusade;

void UIElement::Awake()
{
	Renderer::SetLayer(m_GameObject, 1000);
}

void UIElement::LateTick ()
{
	const auto* camera = Camera::GetMain();
	if (camera == nullptr)
		return;
	auto* cameraTransform = camera->GetTransform();
	auto* transform = GetTransform();

	Vector2f newScale = Scale;
	newScale.x *= 1 / cameraTransform->GetScale().x;
	newScale.y *= 1 / cameraTransform->GetScale().x;

	Vector2f newPosition = Position;
	newPosition *= 1 / cameraTransform->GetScale().x;
	newPosition += cameraTransform->GetPosition();

	transform->SetScale(newScale);
	transform->SetPosition(newPosition);
	transform->SetRotation(rotation);
	
}
