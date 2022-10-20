#include "CrusadePainter.h"
#include "Component.h"
#include "GameObject.h"
using namespace Crusade;

CrusadePainter::CrusadePainter(GameObject* gameObject)
	:Painter()
	,m_GameObject(gameObject)
{
	
}

void CrusadePainter::Render()const
{
	if (!m_GameObject->GetIsActive())
		return;

	for(const auto& component : m_GameObject->GetComponents())
	{
		if (component->GetEnabled())
			component->Render();
	}
}

