#include "Button.h"
#include "GameObject.h"
#include "Camera.h"
#include "Input.h"
#include "Math.h"
using namespace Crusade;

void Button::Awake()
{
	m_Collider = m_GameObject->AddComponent<Collider>();
	m_Renderer = m_GameObject->AddComponent<TextureRenderer>();
	m_Outline = m_GameObject->AddComponent<Outline>();
}

void Button::Tick()
{
	m_Outline->Size = 0;
	const auto worldMousePos = Camera::GetMain()->ScreenToWorld(Input::GetMousePos());
	const auto square = m_Collider->GetHitBox();
	if (Math::IsPointInRect(Point2f{ worldMousePos.x,worldMousePos.y }, square))
	{
		m_Outline->Size = m_OutlineSize;
		if (Input::GetButton("LeftMouseDown"))
		{
			m_Renderer->SetColor(m_SelectColor);
			
		}
		if (Input::GetButton("LeftMouseUp"))
		{
			m_Renderer->SetColor(Color4f{});
			if (m_Action != nullptr)
				m_Action->DoAction();
		}
	}

	if (m_Action != nullptr)
		m_Action->Tick();
}

void Button::OnDestroy()
{
	delete m_Action;
	m_Action = nullptr;
}

void Button::SetAction(ButtonAction* action)
{
	delete m_Action;
	m_Action = action;
}

void Button::SetHighlightColor(const Color4f& color)
{
	m_GameObject->GetComponent<Outline>()->SetColor(color);
}
