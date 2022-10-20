#pragma once
#include "MovementBehavior.h"
namespace Crusade
{
	class Seek final :public MovementBehavior
	{
	public:
		Steering CalculateSteering(float deltaTime, const InputData& inputData) override;
	};
}
