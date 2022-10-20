#include "SceneObject.h"
using namespace Crusade;

int SceneObject::m_NextID = 0;
bool SceneObject::DestroyTrigger = false;

SceneObject::SceneObject()
	:m_ID()
{
	m_ID = m_NextID;
	m_NextID++;
}

void SceneObject::Destroy(SceneObject* object)
{
	object->m_IsDestroyed = true;
	DestroyTrigger = true;
}

void SceneObject::SetIsActive(bool isActive)
{
	m_Enabled = isActive;
}