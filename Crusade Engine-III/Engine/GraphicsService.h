#pragma once
#include "GeneralStucts.h"
#include "Service.h"

namespace Crusade
{
	class GraphicsService : public Service
	{
	public:
		GraphicsService() = default;
		virtual ~GraphicsService() = default;

		GraphicsService(const GraphicsService& other) = delete;
		GraphicsService(GraphicsService&& other) = delete;
		GraphicsService& operator=(const GraphicsService& other) = delete;
		GraphicsService& operator=(GraphicsService&& other) = delete;

		virtual void RenderSquare(const Rectf& square , const float LineWidth)const = 0;
		virtual void RenderCircle(const Circlef& circle, const float LineWidth)const = 0;
		virtual void FillCircle(const Circlef& circle)const = 0;
		virtual void FillSquare(const Rectf& square)const = 0;
		virtual void SetColor(const Color4f& color)const = 0;
		virtual void Translate(float x , float y , float z)const = 0;
		virtual void Rotate(float angle, float x, float y, float z)const = 0;
		virtual void Scale(float x, float y, float z)const = 0;
		virtual void ClearMatrix()const = 0;
	private:
	};
}
