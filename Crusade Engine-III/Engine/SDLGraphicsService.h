#pragma once
#include "GraphicsService.h"
namespace Crusade
{
	class SDLGraphicsService final : public GraphicsService
	{
	public:
		void FillSquare(const Rectf& square) const override;
		void RenderSquare(const Rectf& square , const float LineWidth)const override;
		void SetColor(const Color4f& color)const override;
		void Translate(float x, float y, float z)const override;
		void Rotate(float angle,float x, float y, float z)const override;
		void Scale(float x, float y, float z)const override;
		void ClearMatrix()const override;
		void FillCircle(const Circlef& circle) const override;
		void RenderCircle(const Circlef& circle, const float LineWidth) const override;
	};
}
