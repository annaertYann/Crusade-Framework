#include "GameLoop.h"
#include <chrono>
#include <thread>
#include "ServiceCreator.h"
#include "CrusadeInclude.h"
#include "FPSDebug.h"
#include "CrusadeGame.h"
#include "OpenGLTexture.h"
#include "ServiceLocator.h"
#include "PrefabManager.h"
#include "ResourceService.h"
#include "GraphicsService.h"
#include "EventService.h"
#include "TimeService.h"
#include "AudioService.h"

using namespace std::chrono;
using namespace Crusade;

GameLoop::GameLoop(CrusadeGame* game)
	:m_Game(game)
{
	const HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 2);
	srand(unsigned( time(NULL)));
	
}
GameLoop::~GameLoop()
{
	Exit();
	delete m_Game;
}

void GameLoop::Init()
{
	//SCENE
	SceneManager::GetInstance().CreateScene<NullScene>("NullScene");
	
	//Game
	m_Game->Init();
	
	//RENDERER
	auto* renderer = ServiceCreator::CreateRenderer();
	ServiceLocator::GetInstance().RegisterService<RenderService>(renderer);
	
	//INPUTSYTEM
	auto* input = ServiceCreator::CreateInputSystem();
	ServiceLocator::GetInstance().RegisterService<InputService>(input);

	//RESOURCEMANAGER
	auto* resourceManager = ServiceCreator::CreateResourceManager();
	ServiceLocator::GetInstance().RegisterService<ResourceService>(resourceManager);

	//GRAPHCIS MANAGER
	auto* graphicsManager = ServiceCreator::CreateGraphicsManager();
	ServiceLocator::GetInstance().RegisterService<GraphicsService>(graphicsManager);

	//AUDIO MAANGER
	auto* audioManager = ServiceCreator::CreateAudioManager();
	ServiceLocator::GetInstance().RegisterService<AudioService>(audioManager);

	//Time
	auto* timeServcie = new TimeService();
	ServiceLocator::GetInstance().RegisterService<TimeService>(timeServcie);

	//PREFAB MANAGER
	PrefabManager::GetInstance();
	//auto prefab = PrefabManager::GetPrefab<Decoratation>();

	//EVENT SYSTEM
	auto* eventSystem = new EventService();
	ServiceLocator::GetInstance().RegisterService<EventService>(eventSystem);
	eventSystem->ClearEvents();
}
void GameLoop::Exit()
{
	ProjectSettings::ClearMemory();
	SceneManager::GetInstance().Destroy();
	ServiceLocator::GetInstance().ResetServices();
	PrefabManager::GetInstance().ClearPrefabs();
}

void GameLoop::Run()
{
	Init();

	//SERVICES
	FPSDebug fps{ ProjectSettings::FPSDebugInterval };
	auto* renderer = ServiceLocator::GetInstance().GetService<RenderService>();
	auto* Input = ServiceLocator::GetInstance().GetService<InputService>();

	//INIT TIME
	auto* const deltaTime = new float{};
	ServiceLocator::GetInstance().GetService<TimeService>()->ResetDeltaTime(deltaTime, ProjectSettings::FixedTimeStep);
	auto lastTime = high_resolution_clock::now();
	auto currentTime = high_resolution_clock::now();
	//auto lag = 0.0f;
	//const auto MsPerUpdate = Time::GetFixedDeltaTime();
	
	//GAME LOOP
	auto exitLoop = false;
	Delay sortDelay{0.1f};
	sortDelay.Start();

	while (!exitLoop)
	{
		//HANDLE TIME
		currentTime = high_resolution_clock::now();
		*deltaTime = std::chrono::duration<float>(currentTime - lastTime).count();
		if (*deltaTime >= 0.1f)
			*deltaTime = 0.1f;
		//SLEEP
		auto sleepDuration = (1.f / float(ProjectSettings::MaxFPS) - *deltaTime);
		if (sleepDuration <= 0)
			sleepDuration = 0;
		std::this_thread::sleep_for(duration<double>(sleepDuration));

		if (*deltaTime >= 1.f / float(ProjectSettings::MaxFPS))
		{
			//RESET TIME
			lastTime = currentTime;

			//INPUT
			exitLoop = Input->ProcessInput();
			if (ProjectSettings::Exit)
				exitLoop = true;
			//FIXED UDDATE
			/*lag += *deltaTime;
			while (lag >= MsPerUpdate)
			{
				lag -= MsPerUpdate;
			}*/
			
			//TICK
			m_Game->Tick();
			
			//FPS
			if (ProjectSettings::ShowFPS) { fps.Update(*deltaTime); }
			
			//RENDER
			if (sortDelay.Update(*deltaTime)) { renderer->SortLayers(); sortDelay.Start(); }

			renderer->Render();
		}
	}
}