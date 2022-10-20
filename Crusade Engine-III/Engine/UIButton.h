#pragma once
#include "Prefab.h"
#include "TextureRenderer.h"
#include "UIElement.h"
#include "Button.h"
namespace Crusade
{
	class UIButton : public Prefab
	{
	public:
		std::string Texture = "Crusade/Circle.png";
		Vector2f Size = Vector2f{ 10,10 };
		Vector2f Position{};
		Color4f SelectColor{1,1,1,0.5f };
		Color4f HighlightColor{1,1,1,0.5f};
		float OutlineSize = 1.5f;
		ButtonAction* action = nullptr;
	protected:
		GameObject* CreateObject() override
		{
			auto* object = new GameObject();
			object->SetName("UIButton");

			const auto buttonComp = object->AddComponent<Button>();
			buttonComp->SetHighlightColor(HighlightColor);
			buttonComp->SetOutlineSize(OutlineSize);
			buttonComp->SetSelectColor(SelectColor);
			buttonComp->SetAction(action);

			auto* element = object->AddComponent<UIElement>();
			element->Position = Position;

			auto* renderer = object->AddComponent<TextureRenderer>();
			renderer->SetTexture(Texture);
			renderer->SetSize(Size);

			auto* collider = object->AddComponent<Collider>();
			collider->SetSize(Size);
			action = nullptr;
			return object;
		}
	};
}