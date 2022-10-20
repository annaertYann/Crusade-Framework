#pragma once
#include "Component.h"
#include "Collider.h"
#include "TextureRenderer.h"
#include "Outline.h"

namespace Crusade
{
	class ButtonAction
	{
	public:
		ButtonAction() = default;
		virtual ~ButtonAction() = default;

		ButtonAction(const ButtonAction& other) = delete;
		ButtonAction(ButtonAction&& other) = delete;
		ButtonAction& operator=(const ButtonAction& other) = delete;
		ButtonAction& operator=(ButtonAction&& other) = delete;

		virtual void DoAction() = 0;
		virtual void Tick() {}
	};
	class Button final : public Component
	{
	public:
		void SetAction(ButtonAction* action);
		void SetHighlightColor(const Color4f& color);
		void SetOutlineSize(const float size) { m_OutlineSize = size; }
		void SetSelectColor(const Color4f& color) { m_SelectColor = color; }

	private:
		ButtonAction* m_Action = nullptr;
		Collider* m_Collider = nullptr;
		TextureRenderer* m_Renderer = nullptr;
		Outline* m_Outline = nullptr;
		Color4f m_SelectColor{};
		float m_OutlineSize = 1.5f;

		void Tick() override;
		void Awake() override;
		void OnDestroy() override;
	};
}