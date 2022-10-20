#pragma once
#include "Component.h"
#include "TextureRenderer.h"
namespace Crusade
{
	class Outline final :public Component
	{
	public:
		void SetColor(const Color4f& color);
		Color4f GetColor()const { return m_Color; }
		float Size = 1.15f;
	private:
		Color4f m_Color{ 1,1,1,1 };
		TextureRenderer* m_Renderer = nullptr;

		void Awake() override;
		void Render() const override;
	};
}