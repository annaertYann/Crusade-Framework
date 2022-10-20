#include "SceneManager.h"
#include "Scene.h"
using namespace Crusade;
void SceneManager::Destroy()
{
	for (auto*& scene : *m_Scenes)
	{
		delete scene;
		scene = nullptr;
	}
	m_CurrentScene = nullptr;
	delete m_Scenes;
	m_Scenes = nullptr;
}

void SceneManager::Tick()const
{
	if (!m_CurrentScene)
		return;
	m_CurrentScene->Tick();
}

void SceneManager::LoadScene(const std::string& sceneName)
{
	for (const auto& scene : *m_Scenes)
	{
		if(scene == nullptr)
			continue;

		if (scene->GetName() == sceneName)
		{
			if (m_CurrentScene != nullptr)
				m_CurrentScene->Clear();
			scene->Reset();
			m_CurrentScene = scene;
			return;
		}
	}
	Debug::Print("Scene not found");
}

Scene* SceneManager::GetCurrentScene()const { return m_CurrentScene; }
