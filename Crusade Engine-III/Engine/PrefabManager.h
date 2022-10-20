#pragma once
#include "Prefab.h"
#include "Singleton.h"
namespace Crusade
{
	class PrefabManager final :public Singleton<PrefabManager>
	{
	public:
		void ClearPrefabs()
		{
			if(m_Prefabs != nullptr)
			{
				for (auto*& prefab : *m_Prefabs)
				{
					delete prefab;
					prefab = nullptr;
				}
				m_Prefabs->clear();
				delete m_Prefabs;
				m_Prefabs = nullptr;
			}
		}
		template <typename T>
		static T* GetPrefab();
	private:
		std::vector<Prefab*>* m_Prefabs = nullptr;
	};

	template <typename T>
	T* PrefabManager::GetPrefab()
	{
		auto& prefabs = GetInstance().m_Prefabs;
		if (prefabs == nullptr)
			prefabs = new std::vector<Prefab*>();
		auto prefab = std::find_if(prefabs->begin(), prefabs->end(), [&](Prefab* p) 
			{ return dynamic_cast<T*>(p) != nullptr;  });
		if(prefab == prefabs->end())
		{
			auto p = new T{};
			prefabs->push_back(p);
			return p;
		}
		return dynamic_cast<T*>(*prefab);
	}
}