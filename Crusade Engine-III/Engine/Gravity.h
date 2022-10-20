#pragma once
#include "MovementBehavior.h"

class Gravity final : public MovementBehavior
{
public:
	Steering CalculateSteering(float deltaTime, const InputData& ) override
	{
		Steering steering{ m_Axis,0 };
		steering.linearVelocity = steering.linearVelocity * deltaTime * m_Current;
		m_Current += m_Gravity * deltaTime;
		return steering;
	}

	void SetGravity(const float& gravity) { m_Gravity = gravity; }
	void AddForce(const float force) { m_Current += force; }
	void ResetGravity() { m_Current = 0; }
	void SetAxis(const Vector2f& axis) { m_Axis = axis.Normalized(); }
	float GetGravity()const { return m_Gravity; }
private:
	float m_Gravity{-9.81f};
	float m_Current{};
	Vector2f m_Axis{0,1};
};