#pragma once
#include "MovementBehavior.h"
#include <vector>
namespace Crusade
{
	class Separtaion final :public MovementBehavior
	{
	public:
		std::vector<GameObject*> SeparationGroup;
		float Range = 100;
		Steering CalculateSteering(float deltaTime, const InputData& inputData) override
		{
			if (SeparationGroup.empty())
				return Steering{ Vector2f{},0 };

			auto velocity = Vector2f{};
			for (const auto& element : SeparationGroup)
			{
				if ((element->GetTransform()->GetPosition() - inputData.actorPos).Length() < Range)
				velocity += element->GetTransform()->GetPosition();
			}
			velocity /= float(SeparationGroup.size());
			velocity = velocity - inputData.actorPos;
			velocity = velocity.Normalized();
			velocity *= inputData.maxSpeed * deltaTime;
			velocity *= -1;
			return Steering{ velocity,0 };
		}
	};
}
