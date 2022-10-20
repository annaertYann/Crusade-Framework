#pragma once
#include "Prefab.h"
#include "TextureRenderer.h"
#include "UIElement.h"

namespace Crusade
{
	class UIImage : public Prefab
	{
	public:
	protected:
		GameObject* CreateObject() override
		{
			auto* object = new GameObject();
			object->SetName("UIImage");

			const auto textureRenderer = object->AddComponent<TextureRenderer>();
			textureRenderer->SetTexture(Texture);
			textureRenderer->SetSize(Size, Size);

			auto* element = object->AddComponent<UIElement>();
			element->Position = Position;

			return object;
		}
		std::string Texture = "Crusade/Circle.png";
		float Size = 10;
		Vector2f Position{};
	};
}