#pragma once
#include "MovementBehavior.h"
#include <vector>
namespace Crusade
{
	class Coherency final :public MovementBehavior
	{
	public:
		std::vector<GameObject*> CoherencyGroup;
		float Range = 100;

		Steering CalculateSteering(float deltaTime, const InputData& inputData) override
		{
			if(CoherencyGroup.empty())
				return Steering{ Vector2f{},0 };

			auto velocity = Vector2f{};
			for (const auto& element : CoherencyGroup)
			{
				if ((element->GetTransform()->GetPosition() - inputData.actorPos).Length() < Range)
					velocity += element->GetTransform()->GetPosition();
			}
			velocity /= float(CoherencyGroup.size());
			velocity = velocity - inputData.actorPos;
			velocity = velocity.Normalized();
			velocity *= inputData.maxSpeed * deltaTime;
			return Steering{ velocity,0 };
		}
	};
}
