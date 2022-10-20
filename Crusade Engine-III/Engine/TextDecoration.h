#pragma once
#include "Prefab.h"
#include "TextRenderer.h"

namespace Crusade
{
	class TextDecoratation : public Prefab
	{
	protected:
		GameObject* CreateObject() override
		{
			auto* object = new GameObject();
			object->SetName("TextDecoration");

			const auto textureRenderer = object->AddComponent<TextRenderer>();
			textureRenderer->SetTexture(Texture,Size,Color4f{},"Text");

			return object;
		}
		std::string Texture = "Fonts/Basic.otf";
		float Size = 10;
	};
}