#pragma once
#include "Component.h"
#include "GeneralStucts.h"

namespace Crusade
{
	class Physics final : public Component
	{
	public:
		float Friction = 0.1f;
		float Gravity = 0;
		Vector2f Velocity{};

		void SetGravityAxis(const Vector2f& direction);
		void AddForce(const Vector2f& force);
	private:
		Vector2f m_GravityDirection{ 0,1 };

		void Tick() override;
	};
}