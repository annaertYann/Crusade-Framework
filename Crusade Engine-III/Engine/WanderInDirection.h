#pragma once
#include "CrusadeInclude.h"
namespace Crusade
{
	class WanderInDirection final : public MovementBehavior
	{
	public:
		Steering CalculateSteering(float deltaTime, const InputData& inputData) override;
		void SetMaxAngle(const float angle) { m_Angle = angle; }
		void SetDirection(const Vector2f& direction) { m_Direction = direction; }
		void SetAngleDelay(const float time) { m_Delay = Delay{ time }; }
		void SetAngleChangeSpeed(const float speed) { m_AngleChangeSpeed = speed; }
	private:
		float m_Angle = 70;
		float m_AngleChangeSpeed = 20;
		Vector2f m_Direction{ 0,1 };
		Vector2f m_CurrentDirection{ 0,1 };
		Vector2f m_CurrentDirectionWalk{};
		Delay m_Delay{ 1 };
	};
}