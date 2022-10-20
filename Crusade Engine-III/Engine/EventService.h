#pragma once
#include <vector>
#include "CrusadeEvent.h"
#include "Service.h"
namespace Crusade
{
	class EventService final : public Service
	{
	public:
		EventService() = default;
		 ~EventService() override
		 {
			 ClearEvents();
		 }

		EventService(const EventService& other) = delete;
		EventService(EventService&& other) = delete;
		EventService& operator=(const EventService& other) = delete;
		EventService& operator=(EventService&& other) = delete;

		void AddEvent(CrusadeEvent* newEvent);
		void SendMessage(const std::string& message);
		void ClearEvents();

	private:
		std::vector<CrusadeEvent*>* m_Events = new std::vector<CrusadeEvent*>;
	};
}
