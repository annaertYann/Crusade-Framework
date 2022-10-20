#include "CombinedSteering.h"
#include "GeneralStucts.h"
using namespace Crusade;
MovementBehavior::Steering BlendedSteering::CalculateSteering(float deltaTime, const InputData& inputData)
{
	Steering blendedSteering = {Vector2f{},0};
	auto totalWeight = 0.f;

	for (const auto& weightedBehavior : m_WeightedBehaviors)
	{
		const auto steering = weightedBehavior.pBehavior->CalculateSteering(deltaTime, inputData);
		blendedSteering.linearVelocity += weightedBehavior.weight * steering.linearVelocity;
		blendedSteering.angularVelocity += weightedBehavior.weight * steering.angularVelocity;

		totalWeight += weightedBehavior.weight;
	}

	if (totalWeight > 0.f)
	{
		const auto scale = 1.f / totalWeight;
		blendedSteering.linearVelocity *= scale;
		blendedSteering.angularVelocity *= scale;
	}
	return blendedSteering;
}

void BlendedSteering::AdjustWeight(const int steeringIndex,const float newWeight)
{
	if(steeringIndex < int(m_WeightedBehaviors.size()))
	{
		m_WeightedBehaviors[steeringIndex].weight = newWeight;
	}
}


MovementBehavior::Steering PrioritySteering::CalculateSteering(float deltaTime, const InputData& inputData)
{
	Steering steering = {Vector2f{},0};

	for (const auto pBehavior : m_PriorityBehaviors)
	{
		steering = pBehavior->CalculateSteering(deltaTime, inputData);

		if (steering.isValid)
			break;
	}
	return steering;
}
