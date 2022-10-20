#include "WanderInRange.h"
MovementBehavior::Steering WanderInRange::CalculateSteering(const float deltaTime, const InputData& inputData)
{
	m_Delay.Start();

	if(m_Delay.Update(deltaTime))
	{
		m_Delay.Reset();
		if (m_Range <= 0)
			m_Range = 1;

		if (rand() % 2 == 0)
			m_CurrentTarget = m_Origin + Vector2f{ float(rand() % int(m_Range)), float(rand() % int(m_Range)) };
		else
			m_CurrentTarget = m_Origin - Vector2f{ float(rand() % int(m_Range)), float(rand() % int(m_Range)) };
		m_Seek.SetTarget(m_CurrentTarget);
	}
	return m_Seek.CalculateSteering(deltaTime,inputData);
}
