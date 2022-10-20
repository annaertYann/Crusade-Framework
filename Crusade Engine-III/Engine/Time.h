#pragma once
namespace Crusade
{
	class TimeService;
	class Time final
	{
	public:
		Time() = delete;
		~Time() = delete;
		
		Time(const Time& other) = delete;
		Time(Time&& other) = delete;
		Time& operator=(const Time& other) = delete;
		Time& operator=(Time&& other) = delete;
		
		static float GetDeltaTime();
		static float GetFixedDeltaTime();
	private:
		static TimeService* m_Service;
	};
	
}
