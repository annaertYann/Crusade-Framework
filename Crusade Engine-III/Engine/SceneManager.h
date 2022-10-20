#pragma once
#include <cassert>
#include <vector>
#include "Singleton.h"
#include <string>
#include "Scene.h"
#include "Debug.h"
namespace Crusade
{
	class SceneManager final :public Singleton<SceneManager>
	{
	public:
		template <typename T>
		Scene& CreateScene(const std::string& name);
		
		Scene* GetCurrentScene()const;
		void Tick()const;
		void LoadScene(const std::string& sceneName);

		void Destroy();
	private:
		Scene* m_CurrentScene = nullptr;
		std::vector<Scene*>* m_Scenes = new std::vector<Scene*>{};
	};
	
	template <typename T>
	Scene& SceneManager::CreateScene(const std::string& name)
	{
		static_assert(std::is_base_of<Scene, T>::value, "Creating new scene requires valid scene dervivative ");
		for (const auto& scene : *m_Scenes)
		{
			const auto x = scene->GetName() == name;
			if (x) { Debug::Print("Scene Name Already Used: " + scene->GetName()); }
			assert(!x);
		}
		Scene* scene = new T();
		scene->SetName(name);
		m_Scenes->push_back(scene);
		if(!m_CurrentScene)
		{
			m_CurrentScene = scene;
			m_CurrentScene->Load();
		}
		return *scene;
	}
}
