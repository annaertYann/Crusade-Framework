#pragma once
#include "Component.h"
#include "GeneralStucts.h"
namespace Crusade
{
	class Grid final :public Component
	{
	public:

		Rectf CreateRectFromPoint(const Point2f& point)const;
		void SetGridSize(const float x,const float y) { m_XSize = x; m_YSize = y; }
		Vector2f GetGridSize()const { return Vector2f{ m_XSize,m_YSize }; }
		void SetDebugRender(const bool x) { m_Render = x; }
	private:
		float m_XSize = 1;
		float m_YSize = 1;
		bool m_Render = true;
		void Render() const override;
		void Awake() override;
	};
}
