#pragma once
#include "FPS.h"
#include "Delay.h"
namespace Crusade
{
	class FPSDebug
	{
	public:
		explicit FPSDebug(float updateTime);
		void Update(float deltaTime);
	private:
		FPS m_FPS;
		Delay m_Delay;
	};
}
