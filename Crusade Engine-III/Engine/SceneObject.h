#pragma once
namespace Crusade
{
	class SceneObject
	{
	public:
		SceneObject();
		virtual ~SceneObject() = default;
		
		SceneObject(const SceneObject & other) = delete;
		SceneObject(SceneObject && other) = delete;
		SceneObject& operator=(const SceneObject & other) = delete;
		SceneObject& operator=(SceneObject && other) = delete;

		virtual void PreTick() = 0;
		virtual void Tick() = 0;
		virtual void LateTick() = 0;
		int GetID()const { return m_ID; }

		bool GetIsDestroyed()const { return m_IsDestroyed; }
		static void Destroy(SceneObject* object);

		bool GetIsActive()const { return m_Enabled; }
		virtual void SetIsActive(bool isActive);
		static bool DestroyTrigger;

	protected:	
		int m_ID;
		bool m_Enabled = true;
	private:
		static int m_NextID;
		bool m_IsDestroyed = false;
	};
}
