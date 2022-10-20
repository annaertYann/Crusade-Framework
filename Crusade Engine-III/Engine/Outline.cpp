#include "Outline.h"
#include "Camera.h"
#include "GameObject.h"
#include "Math.h"
#include "Transform.h"
#include "Texture.h"
using namespace Crusade;
void Outline::Awake()
{
	m_Renderer = m_GameObject->AddComponent<TextureRenderer>();

	auto lastElement = m_GameObject->GetComponents().back().get();
	auto firstElement = m_GameObject->GetComponents().front().get();

	m_GameObject->GetComponents()[m_GameObject->GetComponents().size() - 1].release();
	m_GameObject->GetComponents()[0].release();
	m_GameObject->GetComponents()[m_GameObject->GetComponents().size() - 1].reset(firstElement);
	m_GameObject->GetComponents()[0].reset(lastElement);

}

void Outline::SetColor(const Color4f& color)
{
	m_Color = color;
}

void Outline::Render() const
{
	if (m_Renderer == nullptr)
		return;

	auto* texture = m_GameObject->GetComponent<TextureRenderer>()->GetCurrentTexture();

	if (!texture)
		return;

	const auto positon = GetTransform()->GetPosition();
	const auto scale = GetTransform()->GetScale();
	const auto rotation = GetTransform()->GetRotation();

	if (scale.Length() <= 0)
		return;

	const auto width = m_Renderer->GetWidth() * Size;
	const auto height = m_Renderer->GetHeight() * Size;
	const auto offSet = m_Renderer->GetOffSet();

	const auto scaledWidth = width * abs(scale.x);
	const auto scaledHeight = height * abs(scale.y);


	Rectf destRect{ positon.x - scaledWidth / 2,positon.y - scaledHeight / 2,width * scale.x ,height * scale.y };
	destRect.left += offSet.x;
	destRect.bottom += offSet.y;

	if (Camera::GetMain() != nullptr)
		if (!Math::IsOverlapping(Camera::GetMain()->GetCameraWindow(), destRect))
			return;

	texture->SetColor(m_Color);
	texture->Render(destRect, m_Renderer->GetSourceRect(), rotation);
	texture->SetColor(Color4f{1,1,1,1});
}

