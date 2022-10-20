#include "TimeService.h"
#include "Debug.h"
using namespace Crusade;
void TimeService::ResetDeltaTime(float* deltaTime,const int fixedTimeStep)
{
	if (m_HasReset)
	{
		Debug::Print("Time Already Reset : Time::ResetDeltaTime");
		return;
	}

	delete m_DeltaTime;
	m_DeltaTime = deltaTime;
	m_FixedDeltaTime = fixedTimeStep;
	m_HasReset = true;
}
