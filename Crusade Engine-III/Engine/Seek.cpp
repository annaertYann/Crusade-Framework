#include "Seek.h"
using namespace Crusade;
MovementBehavior::Steering Seek::CalculateSteering(float deltaTime, const InputData& inputData)
{
	auto velocity{m_Target - inputData.actorPos};
	velocity = velocity.Normalized();
	velocity *= inputData.maxSpeed * deltaTime;
	return Steering{ velocity,0 };
}