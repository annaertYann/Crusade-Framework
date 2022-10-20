#include "Physics.h"
#include "GameObject.h"
#include "Transform.h"
#include "Time.h"
using namespace Crusade;

void Physics::Tick()
{
	const float deltaTime = Time::GetDeltaTime();
	Velocity += Gravity * deltaTime * m_GravityDirection;

	Velocity.x -= Velocity.x * Friction * deltaTime;
	Velocity.y -= Velocity.y * Friction * deltaTime;

	auto pos = GetTransform()->GetPosition();
	pos += Velocity * deltaTime;
	GetTransform()->SetPosition(pos);
}

void Physics::SetGravityAxis(const Vector2f& direction)
{
	m_GravityDirection = direction.Normalized();
}

void Physics::AddForce(const Vector2f& force)
{
	Velocity += force;
}
