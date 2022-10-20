#include "RenderService.h"
#include <algorithm>
using namespace Crusade;
RenderService::RenderService(const Window& window)
	:m_Window(window)
{
	
}

void RenderService::RegisterPainter(Painter* painter)
{
	const bool found = (std::find_if(m_Painters.begin(), m_Painters.end(), [&](Painter* p) { return p->GetID() == painter->GetID(); }) != m_Painters.end() ) ;

	if (!found)
		m_Painters.push_back(painter);
}

void RenderService::UnRegisterPainter(Painter* painter)
{
	m_Painters.erase(std::remove_if(m_Painters.begin(), m_Painters.end(), [&](Painter* p)
	{
		return painter->GetID() == p->GetID();
	}), m_Painters.end());
}

void RenderService::SortLayers()
{
	std::sort(std::begin(m_Painters), std::end(m_Painters),
		[](Painter* a, Painter* b) { return a->GetLayer() < b->GetLayer(); });
}
