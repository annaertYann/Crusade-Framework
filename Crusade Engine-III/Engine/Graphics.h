#pragma once
#include "GeneralStucts.h"
#include "Window.h"
namespace Crusade
{
	class GraphicsService;
	class RenderService;
	class Graphics final
	{
	public:
		Graphics() = delete;
		~Graphics() = delete;

		Graphics(const Graphics& other) = delete;
		Graphics(Graphics&& other) = delete;
		Graphics& operator=(const Graphics& other) = delete;
		Graphics& operator=(Graphics&& other) = delete;
		static Window GetWindow();
		static void SetColor(const Color4f& color);
		static void RenderSquare(const Rectf& square , float lineWidth);
		static void FillSquare(const Rectf& square);
		static void RenderCircle(const Circlef& circle,float lineWidth);
		static void FillCircle(const Circlef& circle);
		static void ClearMatrix();
		static void Translate(float x, float y , float z);
		static void Scale(float x, float y, float z);
		static void Rotate(float angle, float x, float y, float z);
	private:
		static GraphicsService* m_Service;
		static RenderService* m_RenderService;
		static void InitService();
	};
}
