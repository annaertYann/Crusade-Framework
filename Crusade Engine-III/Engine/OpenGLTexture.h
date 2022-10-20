#pragma once
#include <SDL_opengl.h>
#include <SDL_ttf.h>
#include "Texture.h"
namespace Crusade
{
	class OpenGLTexture final : public Texture
	{
	public:
		explicit OpenGLTexture(const std::string& imagePath);
		explicit OpenGLTexture(const std::string& text, const std::string& fontPath, int ptSize, const Color4f& textColor);
		
		~OpenGLTexture() override;
		
		OpenGLTexture(const Texture& other) = delete;
		OpenGLTexture& operator=(const Texture& other) = delete;
		OpenGLTexture(Texture&& other) = delete;
		OpenGLTexture& operator=(Texture&& other) = delete;
		
		void Render(const Rectf& dstRect, const Rectf& srcRect, float rotation) const override;
		float GetWidth() const override;
		float GetHeight() const override;
		
	private:
		GLuint m_Id;
		float m_Width;
		float m_Height;
		void CreateFromImage(const std::string& path);
		void CreateFromString(const std::string& text, TTF_Font* pFont, const Color4f& textColor);
		void CreateFromString(const std::string& text, const std::string& fontPath, int ptSize, const Color4f& textColor);
		void CreateFromSurface(SDL_Surface* pSurface);
		void DrawFilledRect(const Rectf& dstRect) const;
	};
}
