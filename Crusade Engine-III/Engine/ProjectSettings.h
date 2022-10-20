#pragma once
#include "vector"
#include "CrusadeInclude.h"
namespace Crusade
{
	struct Window;
	struct InputCommand;
	enum class RenderServiceType;
	enum class InputServiceType;
	enum class ResourceManagerType;
	class ProjectSettings final
	{
	public:
		ProjectSettings() = delete;
		~ProjectSettings() = delete;

		ProjectSettings(const ProjectSettings& other) = delete;
		ProjectSettings(ProjectSettings&& other) = delete;
		ProjectSettings& operator=(const ProjectSettings& other) = delete;
		ProjectSettings& operator=(ProjectSettings&& other) = delete;

		static void ClearMemory();
		
		//RENDERER
		static Window* GameWindow;
		static Window* GameReferenceWindow;
		static RenderServiceType GameRenderer;
		//INPUT
		static InputServiceType GameInputSystem;
		static std::vector<InputCommand>* GameInputs;
		//RESOURCE
		static ResourceManagerType ResourceManager;
		//FPS
		static bool ShowFPS;
		static float FPSDebugInterval;
		static int MaxFPS;
		//TIME
		static int FixedTimeStep;
		//Quit
		static bool Exit;
	};

	enum class RenderServiceType
	{
		openGL
	};
	enum class InputServiceType
	{
		Sdl
	};
	enum class ResourceManagerType
	{
		openGL
	};
}
