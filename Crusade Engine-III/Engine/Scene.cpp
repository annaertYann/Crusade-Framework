#include "Scene.h"
#include "SceneObject.h"
#include <algorithm>
#include "Debug.h"

using namespace Crusade;
Scene::~Scene()
{
	std::vector<int> IDs;
	auto vec = m_RemovedObjects;
	for (auto*& object : m_Objects) { vec.push_back(object); }
	for (auto*& object : m_ObjectsToAdd) { vec.push_back(object); }

	vec.erase(std::remove_if(vec.begin(), vec.end(), [&](SceneObject* object)
		{
			bool found = (std::find_if(IDs.begin(), IDs.end(), [&](int& id) { return id == object->GetID(); }) != IDs.end());
			if (!found)
			{
				IDs.push_back(object->GetID());
				return found;
			}
			return found;
		}), vec.end());
	for (auto*& object : vec) { delete object; object = nullptr; }
}


void Scene::Tick()
{
	for (auto* object : m_Objects)
	{
		object->PreTick();
	}
	for (auto* object : m_Objects)
	{
		object->Tick();
	}
	for (auto* object : m_Objects)
	{
		object->LateTick();
	}

	HandleReset();
	AddObjects();
	RemoveObjects();
}

void Scene::Add(SceneObject* object)
{
	bool found = (std::find_if(m_Objects.begin(), m_Objects.end(), [&](SceneObject* p) { return p->GetID() == object->GetID(); }) != m_Objects.end());
	bool found1 = (std::find_if(m_ObjectsToAdd.begin(), m_ObjectsToAdd.end(), [&](SceneObject* p) { return p->GetID() == object->GetID(); }) != m_ObjectsToAdd.end());

	if (!found && !found1)
	m_ObjectsToAdd.push_back(object);
}

void Scene::Remove(SceneObject* object)
{
	bool found = (std::find_if(m_ObjecsToRemove.begin(), m_ObjecsToRemove.end(), [&](SceneObject* p) { return p->GetID() == object->GetID(); }) != m_ObjecsToRemove.end());

	if (!found)
		m_ObjecsToRemove.push_back(object);
}

void Scene::RemoveObjects()
{
	if(!SceneObject::DestroyTrigger)
		return;

	//destroy objects
	m_Objects.erase(std::remove_if(m_Objects.begin(), m_Objects.end(), [&](SceneObject* object)
	{
		const auto isDestoryed = object->GetIsDestroyed();
		if(isDestoryed)
		{
			m_RemovedObjects.erase(std::remove_if(m_RemovedObjects.begin(), m_RemovedObjects.end(), [&](SceneObject* o)
				{
					if (o->GetID() == object->GetID())
					{
						return true;
					}
					return false;
				}), m_RemovedObjects.end());

			delete object;
			return isDestoryed;
		}
		return isDestoryed;
	}), m_Objects.end());
	//Remove objects
	for (auto* o : m_ObjecsToRemove)
	{
		m_Objects.erase(std::remove_if(m_Objects.begin(), m_Objects.end(), [&](SceneObject* object)
			{
				if (o->GetID() == object->GetID())
				{
					m_RemovedObjects.push_back(object);
					return true;
				}
				return false;
			}), m_Objects.end());
	}
	m_ObjecsToRemove.clear();
	SceneObject::DestroyTrigger = false;
}

void Scene::Reset()
{
	m_IsResetting = true;
}

void Scene::HandleReset()
{
	if (m_IsResetting)
	{
		for (auto* object : m_Objects) { SceneObject::Destroy(object); }
		for (auto* object : m_RemovedObjects) { SceneObject::Destroy(object); object->SetIsActive(true); }
		Load();
		m_IsResetting = false;
	}
}
void Scene::Clear()
{
	for (auto* object : m_Objects) { SceneObject::Destroy(object); }
	for (auto* object : m_RemovedObjects) { SceneObject::Destroy(object); object->SetIsActive(true); }
}

std::string Scene::GetName() const { return m_Name; }

void Scene::AddObjects()
{
	for(auto obj : m_ObjectsToAdd)
	{
		m_Objects.push_back(obj);
	}
	m_ObjectsToAdd.clear();
}