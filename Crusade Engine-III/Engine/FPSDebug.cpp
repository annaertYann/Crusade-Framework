#include "FPSDebug.h"
#include "Debug.h"
Crusade::FPSDebug::FPSDebug(const float updateTime)
	:m_FPS()
	,m_Delay(updateTime)
{
	m_Delay.Start();
}

void Crusade::FPSDebug::Update(const float deltaTime)
{
	m_FPS.Update(deltaTime);
	if (m_Delay.Update(deltaTime))
	{
		Debug::Print( "FPS: " + std::to_string(m_FPS.GetFPS()));
		m_Delay.Start();
	}
}
