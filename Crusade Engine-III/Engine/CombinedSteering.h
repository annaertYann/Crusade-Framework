#pragma once
#include <vector>
#include "MovementBehavior.h"
namespace Crusade
{
	class BlendedSteering final : public MovementBehavior
	{
	public:
		struct WeightedBehavior
		{
			MovementBehavior* pBehavior = nullptr;
			float weight = 0.f;

			WeightedBehavior(MovementBehavior* pBehavior, float weight) :
				pBehavior(pBehavior),
				weight(weight)
			{}
		};

		BlendedSteering(std::vector<WeightedBehavior> weightedBehaviors) { m_WeightedBehaviors = weightedBehaviors; }

		void AddBehaviour(WeightedBehavior weightedBehavior) { m_WeightedBehaviors.push_back(weightedBehavior); }
		Steering CalculateSteering(float deltaTime, const InputData& inputData) override;
		void AdjustWeight(int steeringIndex, float newWeight);
	private:
		std::vector<WeightedBehavior> m_WeightedBehaviors = {};
	};

	class PrioritySteering final : public MovementBehavior
	{
	public:
		PrioritySteering(std::vector<MovementBehavior*> priorityBehaviors)
			:m_PriorityBehaviors(priorityBehaviors)
		{}

		void AddBehaviour(MovementBehavior* pBehavior) { m_PriorityBehaviors.push_back(pBehavior); }
		Steering CalculateSteering(float deltaTime, const InputData& inputData) override;

	private:
		std::vector<MovementBehavior*> m_PriorityBehaviors = {};
	};
}