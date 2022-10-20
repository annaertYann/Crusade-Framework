#include "Transform.h"
#include "GameObject.h"
using namespace Crusade;
void Transform::Tick()
{
	const auto& children = m_GameObject->GetChildren();

	if (children.empty())
		return;

	const Vector2f diff = GetPosition() - m_PreviousPos;
	const Vector2f diffScale = GetScale() - m_PreviousScale;
	const float diffRotation = GetRotation() - m_PreviousRotation;
	m_PreviousPos = GetPosition();
	m_PreviousScale = GetScale();
	m_PreviousRotation = GetRotation();

	if (! (diff.Length() >= 0.00001f || diffScale.Length() >= 0.00001f || diffRotation >= 0.00001f) )
		return;

	for (const auto* child : children)
	{
		auto pos = child->GetTransform()->GetPosition();
		pos += diff;
		child->GetTransform()->SetPosition(pos);

		auto rotation = child->GetTransform()->GetRotation();
		rotation += diffRotation;
		child->GetTransform()->SetRotation(rotation);

		auto scale = child->GetTransform()->GetScale();
		scale += diffScale;
		child->GetTransform()->SetScale(scale);
	}
}