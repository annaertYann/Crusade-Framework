#pragma once
#include "CrusadeInclude.h"
namespace Crusade
{
	class WanderInRange final : public MovementBehavior
	{
	public:
		Steering CalculateSteering(float deltaTime, const InputData& inputData) override;
		void SetRange(const float range) { m_Range = range; }
		void SetOrigin(const Vector2f& origin) { m_Origin = origin; }
		void SetSwapTime(const float time) { m_Delay.SetDelayTime(time); }
	private:
		Delay m_Delay{ 1 };
		float m_Range = 100;
		Vector2f m_Origin{};
		Seek m_Seek{};
		Vector2f m_CurrentTarget{};
	};
}