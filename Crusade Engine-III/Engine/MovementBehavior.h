#pragma once
#include "GeneralStucts.h"
namespace Crusade
{
	class MovementBehavior
	{
	public:
		struct Steering
		{
			Steering(const Vector2f& velocity , float angleVelocity):linearVelocity(velocity),angularVelocity(angleVelocity){}
			Vector2f linearVelocity{};
			float angularVelocity = 0;
			bool isValid = false;
		};

		struct InputData
		{
			InputData(const Vector2f& actorPos, const float speed) :actorPos(actorPos),maxSpeed(speed) {}
			Vector2f actorPos{};
			float maxSpeed{};
		};
		
		MovementBehavior() = default;
		virtual ~MovementBehavior() = default;

		MovementBehavior(MovementBehavior& other) = delete;
		MovementBehavior(MovementBehavior&& other) = delete;
		MovementBehavior& operator=(const MovementBehavior& other) = delete;
		MovementBehavior& operator=(MovementBehavior&& other) = delete;
		
		virtual Steering CalculateSteering(float deltaTime, const InputData& inputData) = 0;
		void SetTarget(const Vector2f& target) { m_Target = target; }
	
	protected:
		Vector2f m_Target{};
	};
}
