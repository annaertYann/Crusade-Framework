#pragma once
#include "Prefab.h"
#include "TextureRenderer.h"

namespace Crusade
{
	class Decoratation : public Prefab
	{
	public:
		std::string Texture = "Crusade/Circle.png";
		float Size = 10;
	protected:
		GameObject* CreateObject() override
		{
			auto* object = new GameObject();
			object->SetName("Decoration");

			const auto textureRenderer = object->AddComponent<TextureRenderer>();
			textureRenderer->SetTexture(Texture);
			textureRenderer->SetSize(Size, Size);

			return object;
		}
		
	};
}