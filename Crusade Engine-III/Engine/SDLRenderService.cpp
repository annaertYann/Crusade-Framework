#include "SDLRenderService.h"
#pragma comment(lib, "sdl2.lib")
#pragma comment(lib, "SDL2main.lib")
#pragma comment (lib,"opengl32.lib")
#pragma comment (lib,"Glu32.lib")
#pragma comment(lib, "SDL2_image.lib")  
#pragma comment(lib, "SDL2_ttf.lib") 
#pragma comment(lib, "SDL2_mixer.lib")  
#include <iostream>
#include <SDL.h>
#include <SDL_opengl.h>
#include <GL\GLU.h>
#include <SDL_image.h>
#include <SDL_ttf.h> 
#include "Debug.h"
using namespace Crusade;
SDLRenderService::SDLRenderService(const Window& window)
	:RenderService(window)
{
	Init();
}

void SDLRenderService::Init()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		Debug::Print("Error Creating openglRenderer");
		return;
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

	m_pWindow = SDL_CreateWindow(
		m_Window.title.c_str(),
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		int(m_Window.width),
		int(m_Window.height),
		SDL_WINDOW_OPENGL);
	
	if (m_pWindow == nullptr)
	{
		Debug::Print("Error Creating openglRenderer");
		return;
	}

	m_pContext = SDL_GL_CreateContext(m_pWindow);
	if (m_pContext == nullptr)
	{
		Debug::Print("Error Creating openglRenderer");
		return;
	}

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, m_Window.width, 0, m_Window.height); // y from bottom to top
	glViewport(0, 0, int(m_Window.width), int(m_Window.height));
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	if (SDL_GL_SetSwapInterval(0) == 0)
	{}

	m_Initialized = true;
}

void SDLRenderService::Render() const
{
	if (!m_Initialized) { return; }
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	for (auto* renderer : m_Painters)
	{
		if (renderer != nullptr)
		{
			renderer->Render();
		}
	}

	SDL_GL_SwapWindow(m_pWindow);
}
