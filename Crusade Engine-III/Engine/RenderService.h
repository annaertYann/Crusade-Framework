#pragma once
#include "Window.h"
#include "Painter.h"
#include <vector>
#include "Service.h"

namespace Crusade
{
	class RenderService : public Service
	{
	public:
		explicit RenderService(const Window& window);
		virtual ~RenderService() = default;

		RenderService(const RenderService& other) = delete;
		RenderService(RenderService&& other) = delete;
		RenderService& operator=(const RenderService& other) = delete;
		RenderService& operator=(RenderService&& other) = delete;

		virtual void Render()const = 0;
		void SortLayers();
		Window GetWindow()const { return m_Window; }
		void RegisterPainter(Painter* painter);
		void UnRegisterPainter(Painter* painter);

		std::vector<Painter*>& GetPainters() { return m_Painters; }
	
	protected:
		Window m_Window;
		std::vector<Painter*> m_Painters;
	};
}
