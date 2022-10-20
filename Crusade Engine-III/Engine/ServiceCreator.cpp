#include "ServiceCreator.h"
#include "ProjectSettings.h"
#include "SDLRenderService.h"
#include "SDLInputService.h"
#include "SDLResourceService.h"
#include "SDLGraphicsService.h"
#include "SDLAudioService.h"
using namespace Crusade;

RenderService* ServiceCreator::CreateRenderer()
{
	switch (ProjectSettings::GameRenderer)
	{
	case RenderServiceType::openGL:
		return new SDLRenderService(*ProjectSettings::GameWindow);
		break;
	}
	return nullptr;
}
InputService* ServiceCreator::CreateInputSystem()
{
	switch (ProjectSettings::GameInputSystem)
	{
	case InputServiceType::Sdl:
		return new SDLInputService(*ProjectSettings::GameInputs);
		break;
	}
	return nullptr;
}

ResourceService* ServiceCreator::CreateResourceManager()
{
	switch (ProjectSettings::ResourceManager)
	{
	case ResourceManagerType::openGL:
		return new SDLResourceService();
		break;
	}
	return nullptr;
}

GraphicsService* ServiceCreator::CreateGraphicsManager()
{
	switch (ProjectSettings::GameRenderer)
	{
	case RenderServiceType::openGL:
		return new SDLGraphicsService();
		break;
	}
	return nullptr;
}
AudioService* ServiceCreator::CreateAudioManager()
{
	return new SDLAudioService();
}

