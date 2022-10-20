#pragma once
#include "Component.h"
#include "Particle.h"
class ParticleSystem final : public Crusade::Component
{
public:
	void SetTexture(const std::string& path,float size);
	void SetEmitTime(const float time) { m_Delay.SetDelayTime(time); }

	float ParticleLifeTime = 2;
	int Layer = 10;
	float Gravity = 0;
	float Speed = 0;
	Vector2f Direction{};

private:
	std::string m_ParticlePath{"Crusade/Circle.png"};
	float m_ParticleSize = 0;
	Delay m_Delay{0.2f};

	void Tick() override;
	void Awake() override;
};