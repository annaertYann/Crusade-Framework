#pragma once
#include "Component.h"
#include "GeneralStucts.h"
#include <string>
#include "Texture.h"
namespace Crusade
{
	struct Rectf;
	class TextRenderer final : public Component
	{
	public:
		void SetSize(const float width, const float height) { m_Width = width; m_Height = height; }
		void SetTexture(const std::string& path, float size, const Color4f& color, const std::string& text);
		void Refresh();
		float GetWidth()const { return m_Width; }
		float GetHeight()const { return m_Height; }
		void SetText(const std::string& text);
		void SetColor(const Color4f& color);
		void SetSize(float size);
		Texture* GetCurrentTexture()const { return m_Texture; }
		std::string GetText()const { return m_Text; }
	private:
		void Awake() override;
		void Render() const override;
		void Tick() override;
		void OnDestroy() override;
		bool m_DoRefresh = false;

		Color4f m_Color{};
		float m_Size{};
		std::string m_FontPath{};
		std::string m_Text{};
		Texture* m_Texture = nullptr;
		float m_Width = -1;
		float m_Height = -1;
		Rectf m_SourceRect;
	};
}
