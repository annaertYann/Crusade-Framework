#pragma once
#include <iostream>
namespace Crusade
{
	class CrusadeEvent;
	class EventService;
	class Event final
	{
	public:
		Event() = delete;
		~Event() = delete;

		Event(const Event& other) = delete;
		Event(Event&& other) = delete;
		Event& operator=(const Event& other) = delete;
		Event& operator=(Event&& other) = delete;

		static void SendMessage(const std::string& message);
		static void AddEvent(CrusadeEvent* event);
		static void ClearEvents();
	private:
		static EventService* m_Service;
		static void InitService();
	};
}
