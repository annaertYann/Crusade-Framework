#pragma once
#include <string>
#include <vector>
#include "GeneralStucts.h"
namespace Crusade
{
	class SceneObject;
	class Scene
	{
	public:
		friend class SceneManager;

		virtual ~Scene();
		
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

		void Remove(SceneObject* object);
		void Add(SceneObject* object);
		std::string GetName()const;

	protected:
		Scene() = default;
	private:
		void Tick();
		void SetName(const std::string& name) { m_Name = name; }
		void RemoveObjects();
		void AddObjects();
		void Reset();
		void Clear();
		void HandleReset();
		virtual void Load() = 0;
		
		std::string m_Name;
		std::vector<SceneObject*> m_Objects;
		std::vector<SceneObject*> m_ObjectsToAdd;
		std::vector<SceneObject*> m_RemovedObjects;
		std::vector<SceneObject*> m_ObjecsToRemove;

		bool m_IsResetting = false;
	};
	
	class NullScene final : public Scene
	{
		void Load() override{}
	};
}
