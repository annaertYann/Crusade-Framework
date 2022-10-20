#include "Time.h"
#include "TimeService.h"
#include "ServiceLocator.h"

using namespace Crusade;
TimeService* Time::m_Service = nullptr;

float Time::GetDeltaTime()
{
	if (m_Service == nullptr)
		m_Service = ServiceLocator::GetInstance().GetService<TimeService>();
	if (m_Service == nullptr)
		return 0;
	return m_Service->GetDelatTime();
}
float Time::GetFixedDeltaTime()
{
	if (m_Service == nullptr)
		m_Service = ServiceLocator::GetInstance().GetService<TimeService>();
	if (m_Service == nullptr)
		return 0;
	return float(m_Service->GetFixedDeltaTime()) / 1000.f;
}