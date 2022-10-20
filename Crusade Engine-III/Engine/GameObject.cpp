#include "GameObject.h"
#include "Transform.h"
#include "Time.h" 
#include "SceneManager.h"
using namespace Crusade;
GameObject::GameObject()
	:SceneObject()
{
	m_Name = "GameObject: " + std::to_string(m_ID);
	m_Transform = AddComponent<Transform>();
	AddAsReciever(this);
}

GameObject::~GameObject()
{
	for (int i = 0; i < int(m_Components.size()); i++)
	{
		m_Components[i]->OnDestroy();
	}
}

void GameObject::PreTick()
{
	if (!m_Enabled)
		return;

	for (int i = 0; i < int(m_Components.size()); i++)
	{
		if (m_Components[i]->GetEnabled())
			m_Components[i]->PreTick();
	}
}

void GameObject::Tick()
{
	for (int i = 0; i < int(m_Components.size()); i++)
	{
		if (!m_Components[i]->m_IsStarted)
		{
			m_Components[i]->Start();
			m_Components[i]->m_IsStarted = true;
		}
	}

	if (!m_Enabled)
		return;

	for (int i = 0; i < int(m_Components.size()); i++)
	{
		if (m_Components[i]->GetEnabled())
			m_Components[i]->Tick();
	}
}

void GameObject::LateTick()
{
	if (m_DestoryDelay.Update(Time::GetDeltaTime()))
	{
		Destroy(this);
	}

	if (!m_Enabled)
		return;

	for (int i = 0; i < int(m_Components.size()); i++)
	{
		if (m_Components[i]->GetEnabled())
			m_Components[i]->LateTick();
	}
}


void GameObject::SendMessage(const std::string& message)const
{
	for (const auto* reciever : m_Recievers)
	{
		for (const auto& component : reciever->m_Components)
		{
			component->SendMessage(message);
		}
	}
}

std::vector<std::unique_ptr<Component>>& GameObject::GetComponents() { return m_Components; }

void GameObject::SetName(const std::string& name) { m_Name = name; }
std::string GameObject::GetName() const { return m_Name; }

void GameObject::Destroy(GameObject* gameObject,const float delay)
{
	gameObject->m_DestoryDelay.SetDelayTime(delay);
	gameObject->m_DestoryDelay.Start();
}

void GameObject::Destroy(GameObject* gameObject)
{
	SceneObject::Destroy(gameObject);
	const auto tempChilder = gameObject->m_Children;
	for (int i = 0 ; i < int(tempChilder.size()) ; i ++)
		Destroy(tempChilder[i]);

	if (gameObject->m_Parent != nullptr)
	{
		gameObject->m_Parent->RemoveChild(gameObject);
	}
}

void GameObject::RemoveChild(GameObject* child)
{
	m_Children.erase(std::remove_if(m_Children.begin(), m_Children.end(), [&](const SceneObject* object)
		{
			return object->GetID() == child->GetID();
		}), m_Children.end());
	child->m_Parent = nullptr;
}

void GameObject::AddAsChild(GameObject* child)
{
	if (child->m_Parent != nullptr)
		child->m_Parent->RemoveChild(child);
	m_Children.push_back(child);
	child->m_Parent = this;
}

void GameObject::SetIsActive(const bool isActive)
{
	if (GetIsDestroyed())
		return;

	for (auto* child : m_Children)
	{
		child->SetIsActive(isActive);
	}

	if (m_Enabled != isActive)
	{
		if (isActive)
		{
			SceneManager::GetInstance().GetCurrentScene()->Add(this);
			for (const auto& component : m_Components)
			{
				component->OnEnable();
			}
		}
		else
		{
			SceneManager::GetInstance().GetCurrentScene()->Remove(this);
			for (const auto& component : m_Components)
			{
				component->OnDisable();
			}
		}
	}
	m_Enabled = isActive;
}
