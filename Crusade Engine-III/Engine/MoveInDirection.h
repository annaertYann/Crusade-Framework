#pragma once
#include "MovementBehavior.h"

class MoveInDirection final : public MovementBehavior
{
public:
	Steering CalculateSteering(float deltaTime, const InputData& inputData) override
	{
		Steering steering{ Vector2f{},0 };
		steering.linearVelocity = m_Direction * deltaTime * inputData.maxSpeed;
		return steering;
	}

	void SetDirection(const Vector2f& direction) { m_Direction = direction; }
private:
	Vector2f m_Direction{};
};