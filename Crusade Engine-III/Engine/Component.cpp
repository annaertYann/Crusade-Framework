#include "Component.h"
#include "Debug.h"
#include "GameObject.h"
#include "SceneManager.h"
using namespace Crusade;
void Component::SetGameObject(GameObject* gameObject)
{
	if (m_GameObject)
	{
		Debug::Print("GameObject already set : Component:SetGameObject");
		return;
	}
	
	m_GameObject = gameObject;
}

void Component::PreTick() {}
void Component::Tick() {}
void Component::LateTick() {}
void Component::Start() {}
void Component::Render() const {}
void Component::Awake() {}
void Component::SendMessage(const std::string& ){}
void Component::OnDestroy(){}
void Component::OnDisable() {}
void Component::OnEnable() {}


Transform* Component::GetTransform() const
{
	return m_GameObject->GetTransform();
}
