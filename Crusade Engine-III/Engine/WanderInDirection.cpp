#include "WanderInDirection.h"
using namespace Crusade;
MovementBehavior::Steering WanderInDirection::CalculateSteering(float deltaTime, const InputData& inputData)
{
	m_Delay.Start();
	if(m_Delay.Update(deltaTime))
	{
		m_CurrentDirection = m_Direction;
		float angle = m_Angle;
		angle = float(rand() % int(m_Angle));
		if(rand()%2 ==0)
		{
			angle *= -1;
		}
		angle = Math::DegreeToRadian(angle);
		m_CurrentDirection.x = m_CurrentDirection.x * cos(angle) - m_CurrentDirection.y * sin(angle);
		m_CurrentDirection.y = m_CurrentDirection.x * sin(angle) + m_CurrentDirection.y * cos(angle);
	}

	m_CurrentDirectionWalk.x = Math::MoveTowards(m_CurrentDirectionWalk.x, m_CurrentDirection.x, Math::DegreeToRadian(m_AngleChangeSpeed) * deltaTime);
	m_CurrentDirectionWalk.y = Math::MoveTowards(m_CurrentDirectionWalk.y, m_CurrentDirection.y, Math::DegreeToRadian(m_AngleChangeSpeed) * deltaTime);

	auto velocity = m_CurrentDirectionWalk;
	velocity = velocity.Normalized();
	velocity *= inputData.maxSpeed * deltaTime;
	return Steering{ velocity,0 };
}
