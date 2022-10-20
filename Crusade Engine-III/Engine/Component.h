#pragma once
#include "iostream"
namespace Crusade
{
	class GameObject;
	class Transform;
	class Component
	{
	public:
		friend class GameObject;
		Component() = default;
		virtual ~Component() = default;

		Component(const Component& other) = delete;
		Component(Component&& other) = delete;
		Component& operator=(const Component& other) = delete;
		Component& operator=(Component&& other) = delete;

		virtual void Render()const;
		Transform* GetTransform()const;
		GameObject* GetGameObject()const { return m_GameObject; }

		void SetEnabled(const bool enabled) { m_IsEnabled = enabled; }
		bool GetEnabled()const { return m_IsEnabled; }

	protected:
		GameObject* m_GameObject = nullptr;
	private:
		bool m_IsStarted = false;
		bool m_IsEnabled = true;

		virtual void PreTick();
		virtual void Tick();
		virtual void LateTick();
		virtual void Start();
		virtual void Awake();
		virtual void OnDestroy();
		virtual void OnEnable();
		virtual void OnDisable();
		virtual void SendMessage(const std::string& message);
		void SetGameObject(GameObject* gameObject);
	};
}
