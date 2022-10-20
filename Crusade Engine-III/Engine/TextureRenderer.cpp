#include "TextureRenderer.h"
#include "Renderer.h"
#include "Texture.h"
#include "GameObject.h"
#include "Transform.h"
#include "Resource.h"
#include "Math.h"
#include "Camera.h"
using namespace Crusade;
void TextureRenderer::Awake()
{
	m_GameObject->AddComponent<Renderer>();
}

void TextureRenderer::Render() const
{
	if (!m_Texture)
		return;

	const auto positon = GetTransform()->GetPosition();
	const auto scale = GetTransform()->GetScale();
	const auto rotation = GetTransform()->GetRotation();

	if (scale.Length() <= 0)
		return;

	const auto scaledWidth = m_Width * abs(scale.x);
	const auto scaledHeight = m_Height * abs(scale.y);


	Rectf destRect{ positon.x - scaledWidth / 2,positon.y - scaledHeight / 2,m_Width * scale.x ,m_Height * scale.y };
	destRect.left += m_OffSet.x;
	destRect.bottom += m_OffSet.y;

	if (Camera::GetMain() != nullptr)
		if (!Math::IsOverlapping(Camera::GetMain()->GetCameraWindow(), destRect))
			return;

	m_Texture->SetColor(m_Color);
	//m_Texture->SetColor(Color4f{0,0.1f,0,1});
	m_Texture->Render(destRect,m_SourceRect,rotation);
	m_Texture->SetColor(m_White);
}

void TextureRenderer::SetTexture(const std::string& path,bool isfullPath)
{
	m_Texture = Resource::LoadTexture(path,isfullPath);
}

void TextureRenderer::Tick()
{
	if (!m_Texture)
		return;
	
	if(m_Height < 0 )
	{
		m_Height = m_Texture->GetHeight();
	}

	if (m_Width < 0)
	{
		m_Width = m_Texture->GetWidth();
	}
}

void TextureRenderer::SetColor(const Color4f& color) 
{
	m_Color = color;
}
