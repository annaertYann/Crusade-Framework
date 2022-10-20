#pragma once
namespace Crusade
{
	class Delay
	{
	public:
		explicit Delay(float delayTime);
		
		bool Update(float deltaTime);
		void Start();
		void Stop();
		void Reset();
		
		bool GetActive()const;
		void SetDelayTime(float time);
	
	private:
		float m_MaxTime;
		float m_AccuSec;
		bool m_Active;
	};
}
