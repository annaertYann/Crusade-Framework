#pragma once
#include "CrusadeInclude.h"
namespace Crusade
{
	class Wall final : public Component
	{
	private:
		Collider* m_Collider = nullptr;

		void LateTick() override;
		void Awake() override;
	};
}