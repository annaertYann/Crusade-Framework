#include "EventService.h"

void Crusade::EventService::ClearEvents()
{
	if (m_Events == nullptr)
		return;

	for (auto*& event : *m_Events)
	{
		delete event;
		event = nullptr;
	}
	m_Events->clear();
	delete m_Events;
	m_Events = nullptr;
}

void Crusade::EventService::AddEvent(CrusadeEvent* newEvent)
{
	if (m_Events == nullptr)
		m_Events = new std::vector<CrusadeEvent*>();
	m_Events->push_back(newEvent);
}

void Crusade::EventService::SendMessage(const std::string& message)
{
	if (m_Events == nullptr)
		return;

	for (auto*& event : *m_Events)
	{
		event->SendMessage(message);
	}
}
