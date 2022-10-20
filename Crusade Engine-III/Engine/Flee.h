#pragma once
#include "MovementBehavior.h"
namespace Crusade
{
	class Flee final :public MovementBehavior
	{
	public:
		Steering CalculateSteering(float deltaTime, const InputData& inputData) override
		{
			auto velocity{ m_Target - inputData.actorPos };
			velocity = velocity.Normalized();
			velocity *= inputData.maxSpeed * deltaTime;
			velocity *= -1;
			return Steering{ velocity,0 };
		}
	};
}
