#pragma once
#include "Component.h"
#include "GeneralStucts.h"
namespace Crusade
{
	class UIElement final : public Component
	{
	public:
		Vector2f Position{};
		Vector2f Scale{1,1 };
		float rotation = 0;

	private:
		void LateTick() override;
		void Awake() override;
	};
}