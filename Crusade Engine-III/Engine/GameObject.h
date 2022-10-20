#pragma once
#include <string>
#include "SceneObject.h"
#include <vector>
#include "Component.h"
#include "Delay.h"
#include <memory>
namespace Crusade
{
	class Transform;
	class GameObject final : public SceneObject
	{
	public:
		GameObject();
		~GameObject()override;

		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		void SendMessage(const std::string& message)const;
		void AddAsReciever(GameObject* reciever) { m_Recievers.push_back(reciever); }

		void AddAsChild(GameObject* child);
		GameObject* GetParent()const { return m_Parent; }
		const std::vector<GameObject*>& GetChildren() { return m_Children; }
		void RemoveChild(GameObject* child);

		Transform* GetTransform()const { return m_Transform; }
		std::vector<std::unique_ptr<Component>>& GetComponents();
		template <typename T> T* GetComponent();
		template <typename T> T* AddComponent();
		
		std::string GetName()const;
		void SetName(const std::string& name);
		void SetIsActive(const bool isActive) override;

		static void Destroy(GameObject* gameObject,float delay);
		static void Destroy(GameObject* gameObject);

	private:
		std::vector<std::unique_ptr<Component>> m_Components;
		std::vector<GameObject*> m_Recievers;
		std::vector<GameObject*> m_Children;
		GameObject* m_Parent = nullptr;
		std::string m_Name;
		Transform* m_Transform = nullptr;
		Delay m_DestoryDelay{1};
		
		void Tick() override;
		void LateTick() override;
		void PreTick() override;
	};

	template <typename T>
	T* GameObject::AddComponent()
	{
		if (GetComponent<T>() != nullptr)
			return GetComponent<T>();

		Component* component = new T{};
		if (component == nullptr)
			return nullptr;

		m_Components.push_back(std::unique_ptr<Component>(component));
		component->SetGameObject(this);
		component->Awake();
		return dynamic_cast<T*>(component);
	}


	template <typename T>
	T* GameObject::GetComponent()
	{
		for (const auto& component : m_Components)
		{
			T* temp = dynamic_cast<T*>(component.get());
			if (temp != nullptr)
				return temp;
		}
		return nullptr;
	}
}
