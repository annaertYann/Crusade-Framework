#include "Grid.h"
#include "Graphics.h"
#include "Camera.h"
#include "GameObject.h"
#include "Transform.h"
#include "Renderer.h"
using namespace Crusade;
void Grid::Render() const
{
	if (!m_Render)
		return;
	
	auto window = Graphics::GetWindow();
	const auto numberOfSquares = 20;
	auto pos = GetTransform()->GetPosition();
	auto* camera = Camera::GetMain();
	
	if (camera == nullptr)
		pos = Vector2f{};
	else
		pos = camera->GetTransform()->GetPosition();

	for (int j{}; j < numberOfSquares; j++)
	{
		for (int i{}; i < numberOfSquares; i++)
		{
			Rectf square{ i * m_XSize,j*m_YSize,m_XSize,m_YSize };
			square.left += pos.x - m_XSize * numberOfSquares/2;
			square.bottom += pos.y - m_YSize * numberOfSquares/2;
			Graphics::SetColor(Color4f{255.f,255.f,255.f,255.f});
			Graphics::RenderSquare(square,1);
		}
	}
}

Rectf Grid::CreateRectFromPoint(const Point2f& point)const
{
	auto left{ point.x };
	auto bottom{ point.y };

	const auto diffX = int(left) % int(m_XSize);
	const auto diffY = int(bottom) % int(m_YSize);
	const auto reverseDiffX = m_XSize - abs(float(diffX));
	const auto reverseDiffY = m_XSize - abs(float(diffY));

	if (diffX > 0)
	{
		left = float(int(left - float(diffX)));
	}
	else
	{
		left = float(int(left - reverseDiffX));
	}

	if (diffY > 0)
	{
		bottom = float(int(bottom - float(diffY)));
	}
	else
	{
		bottom = float(int(bottom - reverseDiffY));
	}


	return Rectf{ left,bottom,m_XSize,m_YSize };
}

void Grid::Awake()
{
	m_GameObject->AddComponent < Renderer >();
}
