#include "FPS.h"
void Crusade::FPS::Update(const float deltaTime)
{
	m_AccuSec += deltaTime;
	m_Frames++;
}

int Crusade::FPS::GetFPS()
{
	const auto fps = float(m_Frames) / m_AccuSec ;
	m_Frames = 0;
	m_AccuSec = 0;
	return int(float(fps) + 0.5f);
	
}
