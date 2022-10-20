#pragma once
#include "GameObject.h"
#include "GeneralStucts.h"
namespace Crusade
{
	class PrefabManager;
	class Prefab
	{
	public:
		Prefab() = default;
		virtual ~Prefab() = default;

		Prefab(const Prefab& other) = delete;
		Prefab(Prefab&& other) = delete;
		Prefab& operator=(const Prefab& other) = delete;
		Prefab& operator=(Prefab&& other) = delete;

		GameObject* Instantiate(const Vector2f& pos = {}, const float rotation = {}, const Vector2f& scale = Vector2f{ 1,1 });
		GameObject* Instantiate(GameObject* parent);
	protected:
		virtual GameObject* CreateObject() = 0;
	};
}
