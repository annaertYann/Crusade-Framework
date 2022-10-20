#pragma once
#include "Painter.h"
namespace Crusade
{
	class Component;
	class GameObject;
	class CrusadePainter final : public Painter
	{
	public:
		explicit CrusadePainter(GameObject* gameObject);
		void Render()const override;
		GameObject* GetGameObject()const { return m_GameObject; }

	private:
		GameObject* m_GameObject;
	};
}
