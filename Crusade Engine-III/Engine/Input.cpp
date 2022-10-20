#include "Input.h"
#include "ServiceLocator.h"
#include "InputService.h"
using namespace Crusade;
InputService* Input::m_Service = nullptr;
float Input::GetAxis(const std::string& name)
{
	InitService();
	if (m_Service == nullptr)
		return 0;
	return m_Service->GetAxis(name);
}

bool Input::GetButton(const std::string& name)
{
	InitService();
	if (m_Service == nullptr)
		return false;
	return m_Service->GetButton(name);
}

Vector2f Input::GetMousePos() 
{
	InitService();
	if (m_Service == nullptr)
		return Vector2f{};
	return m_Service->GetMousePos();
}

float Input::GetScrollMotion()
{
	InitService();
	if (m_Service == nullptr)
		return 0;
	return m_Service->GetScrollWheelMotion();
}
void Input::InitService()
{
	if (m_Service == nullptr)
		m_Service = ServiceLocator::GetInstance().GetService<InputService>();
}
