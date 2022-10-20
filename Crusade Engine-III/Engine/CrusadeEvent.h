#pragma once
#include <string>
namespace Crusade
{
	class CrusadeEvent
	{
	public:
		CrusadeEvent() = default;
		virtual ~CrusadeEvent() = default;

		CrusadeEvent(const CrusadeEvent& other) = delete;
		CrusadeEvent(CrusadeEvent&& other) = delete;
		CrusadeEvent& operator=(const CrusadeEvent& other) = delete;
		CrusadeEvent& operator=(CrusadeEvent&& other) = delete;

		virtual void SendMessage(const std::string& message) = 0;

	};
}