#include "Event.h"
#include "EventService.h"
#include "ServiceLocator.h"
using namespace Crusade;
EventService* Event::m_Service = nullptr;

void Crusade::Event::SendMessage(const std::string& message)
{
	InitService();
	if (m_Service == nullptr)
		return;

	m_Service->SendMessage(message);
}

void Crusade::Event::ClearEvents()
{
	InitService();
	if (m_Service == nullptr)
		return;

	m_Service->ClearEvents();
}

void Crusade::Event::AddEvent(CrusadeEvent* event)
{
	InitService();
	if (m_Service == nullptr)
		return;

	m_Service->AddEvent(event);
}

void Event::InitService()
{
	if (m_Service == nullptr)
		m_Service = ServiceLocator::GetInstance().GetService<EventService>();
}
