#include "Texture.h"
int Crusade::Texture::NextTag = 0;

using namespace Crusade;
Texture::Texture(const std::string& imagePath)
	:m_ImagePath( imagePath)
	, m_Text()
	, m_FonthPath()
	, m_PtSize()
	, m_Color()
{
	m_Tag = NextTag;
	NextTag++;
}

Texture::Texture(const std::string& text, const std::string& fontPath, int ptSize, const Color4f& textColor)
	:m_ImagePath()
	,m_Text(text)
	,m_FonthPath(fontPath)
	, m_PtSize(ptSize)
	,m_Color(textColor)
{
	m_IsText = true;
	m_Tag = NextTag;
	NextTag++;
}

std::string Texture::GetPath() const
{
	if (this == nullptr)
		return std::string{  };

	if (m_IsText)
		return m_FonthPath;

	return m_ImagePath;
}
