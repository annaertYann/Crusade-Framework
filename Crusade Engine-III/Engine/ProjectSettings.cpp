#include "ProjectSettings.h"
using namespace Crusade;

void ProjectSettings::ClearMemory()
{
	std::vector<InputCommand>().swap(*GameInputs);
	delete GameInputs;
	delete GameWindow;
	delete GameReferenceWindow;
}

//RENDERER
RenderServiceType ProjectSettings::GameRenderer = RenderServiceType::openGL;
Window* ProjectSettings::GameWindow = new Window{"CrusadeEngine",1920,1080,false};
Window* ProjectSettings::GameReferenceWindow = new Window{ "CrusadeEngine",1024,576,false };
//INPUT
InputServiceType ProjectSettings::GameInputSystem = InputServiceType::Sdl;
std::vector<InputCommand>* ProjectSettings::GameInputs = new std::vector<InputCommand>
{
	InputCommand{InputCommandType::axis,"Horizontal",Command::d,Command::a},
	InputCommand{InputCommandType::axis,"Vertical",Command::w,Command::s},
	InputCommand{InputCommandType::button,"Fire",Command::leftMouseButton,Command::leftMouseButton,ButtonType::down}
	,InputCommand{InputCommandType::button,"Up",Command::up,Command::leftMouseButton,ButtonType::down}
	,InputCommand{InputCommandType::button,"Down",Command::down,Command::leftMouseButton,ButtonType::down}
	,InputCommand{InputCommandType::button,"Left",Command::left,Command::leftMouseButton,ButtonType::down}
	,InputCommand{InputCommandType::button,"Right",Command::right,Command::leftMouseButton,ButtonType::down}
	,InputCommand{InputCommandType::button,"Interact",Command::e,Command::leftMouseButton,ButtonType::down}
	,InputCommand{InputCommandType::button,"Esc",Command::esc,Command::esc,ButtonType::down }
	,InputCommand{InputCommandType::button,"LeftMouseUp",Command::leftMouseButton,Command::leftMouseButton,ButtonType::released}
	,InputCommand{InputCommandType::button,"LeftMouse",Command::leftMouseButton,Command::leftMouseButton,ButtonType::released}
	,InputCommand{InputCommandType::button,"LeftMouseDown",Command::leftMouseButton,Command::leftMouseButton,ButtonType::down}
	,InputCommand{InputCommandType::button,"RightMouseUp",Command::rightMouseButton,Command::rightMouseButton,ButtonType::released}
	,InputCommand{InputCommandType::button,"RightMouse",Command::rightMouseButton,Command::rightMouseButton,ButtonType::released}
	,InputCommand{InputCommandType::button,"RightMouseDown",Command::rightMouseButton,Command::rightMouseButton,ButtonType::down}
	,InputCommand{InputCommandType::button,"Boost",Command::leftShift,Command::rightMouseButton,ButtonType::pressed}
	,InputCommand{InputCommandType::axis,"ScrollWheel",Command::scrollWheel,Command::scrollWheel},
};
//RESOURCE
ResourceManagerType ProjectSettings::ResourceManager = ResourceManagerType::openGL;
//FPS
bool ProjectSettings::ShowFPS = true;
float ProjectSettings::FPSDebugInterval = 3;
int ProjectSettings::MaxFPS = 120;

//TIME
int ProjectSettings::FixedTimeStep = 1;

//Quit
bool ProjectSettings::Exit = false;