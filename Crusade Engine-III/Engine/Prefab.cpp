#include "Prefab.h"
#include "Transform.h"
#include "CrusadeInclude.h"
using namespace Crusade;
GameObject* Prefab::Instantiate(const Vector2f& pos, const float rotation, const Vector2f& scale)
{
	auto* obj = CreateObject();

	if (obj == nullptr)
		return nullptr;

	obj->GetTransform()->SetPosition(pos);
	obj->GetTransform()->SetRotation(rotation);
	obj->GetTransform()->SetScale(scale);

	SceneManager::GetInstance().GetCurrentScene()->Add(obj);
	
	return obj;
}

GameObject* Prefab::Instantiate(GameObject* parent)
{
	auto* obj = CreateObject();

	if (obj == nullptr)
		return nullptr;

	obj->GetTransform()->SetPosition(parent->GetTransform()->GetPosition());
	obj->GetTransform()->SetRotation(parent->GetTransform()->GetRotation());
	obj->GetTransform()->SetScale(parent->GetTransform()->GetScale());
	parent->AddAsChild(obj);

	SceneManager::GetInstance().GetCurrentScene()->Add(obj);

	return obj;
}
