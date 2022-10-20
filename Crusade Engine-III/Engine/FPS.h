#pragma once
namespace Crusade
{
	class FPS
	{
	public:
		FPS() = default;
		void Update(float deltaTime);
		int GetFPS();
	private:
		int m_Frames = 0;
		float m_AccuSec = 0;
	};
}
