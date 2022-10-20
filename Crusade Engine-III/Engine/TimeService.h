#pragma once
#include "Service.h"
namespace Crusade
{
	class TimeService final : public Service
	{
	public:
		TimeService() = default;
		~TimeService() override
		{
			delete m_DeltaTime;
			m_DeltaTime = nullptr;
		}

		TimeService(const TimeService& other) = delete;
		TimeService(TimeService&& other) = delete;
		TimeService& operator=(const TimeService& other) = delete;
		TimeService& operator=(TimeService&& other) = delete;

		float GetDelatTime()const { return *m_DeltaTime; }
		int GetFixedDeltaTime()const { return m_FixedDeltaTime; }
		void ResetDeltaTime(float* deltaTime,int fixedTimeStep);
	private:
		float* m_DeltaTime = new float();
		int m_FixedDeltaTime = 16;
		bool m_HasReset = false;
	};
}
