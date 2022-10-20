#include "Painter.h"
using namespace Crusade;
int Painter::m_NextID = 0;

Painter::Painter()
	:m_ID()
{
	m_ID = m_NextID;
	m_NextID++;
}

void Painter::SetLayer(const int& layer)
{
	m_Layer = layer;
}