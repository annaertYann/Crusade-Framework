#pragma once
#include <SDL_video.h>
#include "RenderService.h"
namespace Crusade
{
	class SDLRenderService final : public RenderService
	{
	public:
		explicit  SDLRenderService(const Window& window);
		void Render()const override;
	private:
		void Init();
		SDL_Window* m_pWindow;
		SDL_GLContext m_pContext;
		bool m_Initialized;
	};
}
