#pragma once
#include "Component.h"
#include "GeneralStucts.h"
#include <string>
#include "GeneralStucts.h"
namespace Crusade
{
	struct Rectf;
	class Texture;
	class TextureRenderer final : public Component
	{
	public:
		void SetSize(const float width, const float height) { m_Width = width; m_Height = height; }
		void SetSize(const Vector2f& size) { m_Width = size.x; m_Height = size.y; }

		void SetTexture(const std::string& path,bool isFullPaht = false);
		void SetTexture(Texture* texture) { m_Texture = texture; }
		Texture* GetCurrentTexture()const { return m_Texture; }
		
		float GetWidth()const { return m_Width; }
		float GetHeight()const { return m_Height; }

		Rectf GetSourceRect()const { return m_SourceRect; }
		void SetSourceRect(const Rectf& sourceRect) { m_SourceRect = sourceRect; }
		Vector2f GetOffSet()const { return m_OffSet; }
		void SetOffSet(const float x, const float y) { m_OffSet.x = x; m_OffSet.y = y; }
		void SetColor(const Color4f& color);

	private:
		void Awake() override;
		void Render() const override;
		void Tick() override;
		
		Texture* m_Texture = nullptr;
		float m_Width = -1;
		float m_Height = -1;
		Rectf m_SourceRect;
		Vector2f m_OffSet{};
		Color4f m_Color{0,0,0,0};
		Color4f m_White{0,0,0,0};
	};
}
