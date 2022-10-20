#include "Delay.h"
using namespace Crusade;

Delay::Delay(const float delayTime)
	:m_MaxTime(delayTime)
	,m_AccuSec()
	,m_Active()
{
	
}

bool Delay::Update(const float deltaTime)
{
	if (!m_Active)
		return false;
	
	m_AccuSec += deltaTime;
	if(m_AccuSec >= m_MaxTime)
	{
		m_AccuSec = 0;
		return true;
	}
	return false;
}

void Delay::Start() { m_Active = true; }
void Delay::Stop() { m_Active = false; }
void Delay::Reset() { m_AccuSec = 0; }
bool Delay::GetActive()const { return m_Active; }
void Delay::SetDelayTime(const float time) { m_MaxTime = time; }
