#pragma once
#include <string>
#include "GeneralStucts.h"
namespace Crusade
{
	class Texture
	{
	public:
		explicit Texture(const std::string& imagePath);
		explicit Texture(const std::string& text, const std::string& fontPath, int ptSize, const Color4f& textColor);

		virtual ~Texture() = default;
		Texture(const Texture& other) = delete;
		Texture& operator=(const Texture& other) = delete;
		Texture(Texture&& other) = delete;
		Texture& operator=(Texture&& other) = delete;

		virtual void Render(const Rectf& dstRect, const Rectf& srcRect = {} , float rotation = {}) const = 0;

		virtual float GetWidth() const = 0;
		virtual float GetHeight() const = 0;
		std::string GetPath()const;
		bool IsCreationOk() const { return m_CreationOk; }
		
		void SetText(const std::string& text) { m_Text = text; }
		void SetColor(const Color4f& color) { m_Color = color; }
		int GetTag()const { return m_Tag; }
	
	protected:
		std::string m_ImagePath;
		std::string m_Text;
		std::string m_FonthPath;
		int m_PtSize;
		bool m_IsText = false;
		bool m_CreationOk = false;
		Color4f m_Color{0,0,0,0};
	private:
		int m_Tag = 0;
		static int NextTag;
	};
}
