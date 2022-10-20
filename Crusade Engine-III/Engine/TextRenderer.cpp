#include "TextRenderer.h"
#include "Renderer.h"
#include "Texture.h"
#include "GameObject.h"
#include "Transform.h"
#include "Resource.h"
using namespace Crusade;
void TextRenderer::Awake()
{
	m_GameObject->AddComponent<Renderer>();
}

void TextRenderer::Render() const
{
	if (!m_Texture)
		return;

	const auto positon = GetTransform()->GetPosition();
	const auto scale = GetTransform()->GetScale();
	const auto rotation = GetTransform()->GetRotation();

	if (scale.Length() <= 0)
		return;
	const auto scaledWidth = (m_Width * abs(scale.x))  ;
	const auto scaledHeight = (m_Height * abs(scale.y))  ;


	const Rectf destRect{ positon.x - scaledWidth / 2,positon.y - scaledHeight / 2,m_Width * scale.x ,m_Height * scale.y };
	m_Texture->Render(destRect, m_SourceRect, rotation);
}

void TextRenderer::SetTexture(const std::string& path, float size, const Color4f& color, const std::string& text)
{
	m_Color = color;
	m_FontPath = path;
	m_Text = text;
	m_Size = size;

	m_DoRefresh = true;
}

void TextRenderer::OnDestroy()
{
	if (m_Texture != nullptr)
		Resource::RemoveTexture(m_Texture);
}


void TextRenderer::Refresh()
{
	m_Width = -1;
	m_Height = -1;
	if (m_Texture != nullptr)
		Resource::RemoveTexture(m_Texture);
	
	if (!m_Text.empty())
		m_Texture = Resource::LoadTextTexture(m_FontPath,unsigned (m_Size), m_Text, m_Color);
	else
		m_Texture = Resource::LoadTextTexture(m_FontPath, unsigned (m_Size), " ", m_Color);
}

void TextRenderer::Tick()
{
	if (m_DoRefresh)
	{
		m_DoRefresh = false;
		Refresh();
	}

	if (!m_Texture)
		return;

	if (m_Height < 0)
	{
		m_Height = m_Texture->GetHeight();
	}

	if (m_Width < 0)
	{
		m_Width = m_Texture->GetWidth();
	}
	
}

void TextRenderer::SetText(const std::string& text)
{
	m_Text = text;
	m_DoRefresh = true;
}
void TextRenderer::SetColor(const Color4f& color)
{
	m_Color = color;
	m_DoRefresh = true;
}
void TextRenderer::SetSize(float size)
{
	m_Size = size;
	m_DoRefresh = true;
}