#include "Renderer.h"
#include "CrusadePainter.h"
#include "GameObject.h"
#include "ServiceLocator.h"
#include "RenderService.h"
using namespace Crusade;
void Renderer::Awake()
{
	m_Painter = new CrusadePainter{ m_GameObject };
}
void Renderer::Start()
{
	RegisterPainter(m_Painter);
	SetLayer(m_Layer);
}

void Renderer::RegisterPainter(Painter* painter)
{
	ServiceLocator::GetInstance().GetService<RenderService>()->RegisterPainter(painter);
}
void Renderer::UnRegisterPainter(Painter* painter)
{
	ServiceLocator::GetInstance().GetService<RenderService>()->UnRegisterPainter(painter);
}

void Renderer::SetLayer(const int& layer)
{
	m_Layer = layer;
	if (m_Painter != nullptr)
		m_Painter->SetLayer(m_Layer);
}

void Renderer::SetLayer(GameObject* object, const int& layer)
{
	auto* renderer = object->AddComponent<Renderer>();
	renderer->SetLayer(layer);
}

void Renderer::OnDestroy()
{
	UnRegisterPainter(m_Painter);
	delete m_Painter;
	m_Painter = nullptr;
}

void Renderer::OnDisable()
{
	UnRegisterPainter(m_Painter);
}

void Renderer::OnEnable()
{
	RegisterPainter(m_Painter);
}

