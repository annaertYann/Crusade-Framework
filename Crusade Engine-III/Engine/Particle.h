#pragma once
#include "CrusadeInclude.h"

class Particle final :public Component
{
public:
	void SetData(const Vector2f& direction, float speed, float gravity)
	{
		m_Direction = direction;
		m_Speed = speed;
		m_Gravity = gravity;
	}

private:
	Vector2f m_Direction{};
	float m_Speed = 0;
	float m_Gravity = 0;
	float m_CurrentVelocity = 0;


	void Tick() override
	{
		const float delta = Time::GetDeltaTime();
		m_CurrentVelocity += m_Gravity * delta;
		auto pos = GetTransform()->GetPosition();
		pos += m_Direction * m_Speed * delta;
		pos.y += m_CurrentVelocity * delta;
		GetTransform()->SetPosition(pos);
	}
};