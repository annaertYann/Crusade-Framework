#include "ParticleSystem.h"
#include "PrefabManager.h"

void ParticleSystem::SetTexture(const std::string& path,float size)
{
	m_ParticlePath = path;
	m_ParticleSize = size;
}
void ParticleSystem::Awake()
{
	m_Delay.Start();
}

void ParticleSystem::Tick()
{
	if(m_Delay.Update(Time::GetDeltaTime()))
	{
		m_Delay.Start();
		auto* obj = new GameObject();

		obj->GetTransform()->SetPosition(GetTransform()->GetPosition());
		obj->GetTransform()->SetRotation(GetTransform()->GetRotation());
		obj->GetTransform()->SetScale(GetTransform()->GetScale());

		obj->AddComponent<TextureRenderer>()->SetTexture(m_ParticlePath);
		obj->AddComponent<TextureRenderer>()->SetSize(m_ParticleSize,m_ParticleSize);

		auto* particle = obj->AddComponent<Particle>();
		particle->SetData(Direction, Speed, Gravity);

		obj->AddComponent<Renderer>()->SetLayer(Layer);
		SceneManager::GetInstance().GetCurrentScene()->Add(obj);

		GameObject::Destroy(obj, ParticleLifeTime);
	}
}