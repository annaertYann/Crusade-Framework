#pragma once
#include "Prefab.h"
#include "TextRenderer.h"
#include "UIElement.h"

namespace Crusade
{
	class UITextImage : public Prefab
	{
	public:
	protected:
		GameObject* CreateObject() override
		{
			auto* object = new GameObject();
			object->SetName("UITextImage");

			const auto textureRenderer = object->AddComponent<TextRenderer>();
			textureRenderer->SetTexture(Texture,Size,Color4f{},"Text");

			auto* element = object->AddComponent<UIElement>();
			element->Position = Position;

			return object;
		}
		std::string Texture = "Fonts/Basic.otf";
		float Size = 10;
		Vector2f Position{};
	};
}