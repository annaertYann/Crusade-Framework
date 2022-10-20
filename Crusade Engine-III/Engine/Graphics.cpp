#include "Graphics.h"
#include "ServiceLocator.h"
#include "GraphicsService.h"
#include "RenderService.h"
using namespace Crusade;
GraphicsService* Graphics::m_Service = nullptr;
RenderService* Graphics::m_RenderService = nullptr;
void Graphics::RenderSquare(const Rectf& square,const float lineWidth)
{
	InitService();
	if (m_Service == nullptr)
		return;
	m_Service->RenderSquare(square, lineWidth);
}

void Graphics::FillSquare(const Rectf& square)
{
	InitService();
	if (m_Service == nullptr)
		return;
	m_Service->FillSquare(square);
}

void Graphics::SetColor(const Color4f& color)
{
	InitService();
	if (m_Service == nullptr)
		return;
	m_Service->SetColor(color);
}

void Graphics::FillCircle(const Circlef& circle)
{
	InitService();
	if (m_Service == nullptr)
		return;
	m_Service->FillCircle(circle);
}

void Graphics::RenderCircle(const Circlef& circle, const float lineWidth)
{
	InitService();
	if (m_Service == nullptr)
		return;
	m_Service->RenderCircle(circle,lineWidth);
}

void Graphics::ClearMatrix() 
{
	InitService();
	if (m_Service == nullptr)
		return;
	m_Service->ClearMatrix();
}

void Graphics::Translate(float x, float y, float z)
{
	InitService();
	if (m_Service == nullptr)
		return;
	m_Service->Translate(x,y,z);
}

void Graphics::Rotate(float angle, float x, float y, float z)
{
	InitService();
	if (m_Service == nullptr)
		return;
	m_Service->Rotate(angle,x, y, z);
}

void Graphics::Scale(float x, float y, float z)
{
	InitService();
	if (m_Service == nullptr)
		return;

	m_Service->Scale(x, y, z);
}

Window Graphics::GetWindow()
{
	if (m_RenderService == nullptr)
		m_RenderService = ServiceLocator::GetInstance().GetService<RenderService>();
	if (m_RenderService == nullptr)
		return Window{};
	return m_RenderService->GetWindow();
}

void Graphics::InitService()
{
	if (m_Service == nullptr)
		m_Service = ServiceLocator::GetInstance().GetService<GraphicsService>();
}
