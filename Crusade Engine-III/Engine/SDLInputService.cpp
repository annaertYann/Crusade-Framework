#include "SDLInputService.h"
#include <SDL_events.h>
using namespace Crusade;
SDLInputService::SDLInputService(const std::vector<InputCommand>& commandList)
	:InputService(commandList)
	,m_E()
{
	CreateCommandValues();
}

bool SDLInputService::ProcessInput()
{

	for (auto& command : m_InputCommands)
	{
		switch (command.commandType)
		{
		case InputCommandType::axis:
			ProcessAxis(command);
			break;
		case InputCommandType::button:
			ProcessButton(command);
			break;
		}

	}

	int x{};
	int y{};
	SDL_GetMouseState(&x, &y);
	m_MousePos = Vector2f{ float(x),float(y) };

	m_ScroolWheelMotion = 0;
	while (SDL_PollEvent(&m_E) != 0)
	{
		switch (m_E.type)
		{
		case SDL_QUIT:
			return true;
			break;
		}

		if (m_E.type == SDL_MOUSEWHEEL)
		{
			m_ScroolWheelMotion = float(m_E.wheel.y);
		}

	}
	return false;
}

void SDLInputService::ProcessAxis( InputCommand& command)
{
	command.axisValue = 0;
	if(IsButtonPressed(command.positiveButton,m_SDLCommandValues[command.positiveButton]))
	{
		command.axisValue = 1;
	}
	if (IsButtonPressed(command.negativeButton, m_SDLCommandValues[command.negativeButton]))
	{
		if(command.axisValue >= 1)
		{
			command.axisValue = 0;
			return;
		}
		command.axisValue = -1;
	}
}

void SDLInputService::ProcessButton(InputCommand& command)
{
	if (IsButtonPressed(command.positiveButton, m_SDLCommandValues[command.positiveButton]))
	{
		switch (command.buttonType)
		{
		case ButtonType::down:
			if(!command.isDown)
			{
				command.active = true;
				command.isDown = true;
			}
			else
				command.active = false;
			break;
		case ButtonType::pressed:
			command.active = true;
			command.isDown = true;
			break;
		case ButtonType::released:
			command.isDown = true;
			command.active = false;
			break;
		}
	}
	else
	{
		switch (command.buttonType)
		{
		case ButtonType::down:
			command.isDown = false;
			command.active = false;
			break;
		case ButtonType::pressed:
			command.isDown = false;
			command.active = false;
			break;
		case ButtonType::released:
			if (command.isDown)
			{
				command.active = true;
				command.isDown = false;
			}
			else
				command.active = false;
			break;
		}
	}
}

void SDLInputService::CreateCommandValues()
{
	m_SDLCommandValues.insert(std::pair<Command, int>{Command::a, SDL_SCANCODE_A});
	m_SDLCommandValues.insert(std::pair<Command, int>{Command::b, SDL_SCANCODE_B});
	m_SDLCommandValues.insert(std::pair<Command, int>{Command::c, SDL_SCANCODE_C});
	m_SDLCommandValues.insert(std::pair<Command, int>{Command::d, SDL_SCANCODE_D});
	m_SDLCommandValues.insert(std::pair<Command, int>{Command::e, SDL_SCANCODE_E});
	m_SDLCommandValues.insert(std::pair<Command, int>{Command::f, SDL_SCANCODE_F});
	m_SDLCommandValues.insert(std::pair<Command, int>{Command::g, SDL_SCANCODE_G});
	m_SDLCommandValues.insert(std::pair<Command, int>{Command::h, SDL_SCANCODE_H});
	m_SDLCommandValues.insert(std::pair<Command, int>{Command::i, SDL_SCANCODE_I});
	m_SDLCommandValues.insert(std::pair<Command, int>{Command::j, SDL_SCANCODE_J});
	m_SDLCommandValues.insert(std::pair<Command, int>{Command::k, SDL_SCANCODE_K});
	m_SDLCommandValues.insert(std::pair<Command, int>{Command::l, SDL_SCANCODE_L});
	m_SDLCommandValues.insert(std::pair<Command, int>{Command::m, SDL_SCANCODE_M});
	m_SDLCommandValues.insert(std::pair<Command, int>{Command::n, SDL_SCANCODE_N});
	m_SDLCommandValues.insert(std::pair<Command, int>{Command::o, SDL_SCANCODE_O});
	m_SDLCommandValues.insert(std::pair<Command, int>{Command::p, SDL_SCANCODE_P});
	m_SDLCommandValues.insert(std::pair<Command, int>{Command::q, SDL_SCANCODE_Q});
	m_SDLCommandValues.insert(std::pair<Command, int>{Command::r, SDL_SCANCODE_R});
	m_SDLCommandValues.insert(std::pair<Command, int>{Command::s, SDL_SCANCODE_S});
	m_SDLCommandValues.insert(std::pair<Command, int>{Command::t, SDL_SCANCODE_T});
	m_SDLCommandValues.insert(std::pair<Command, int>{Command::u, SDL_SCANCODE_U});
	m_SDLCommandValues.insert(std::pair<Command, int>{Command::v, SDL_SCANCODE_V});
	m_SDLCommandValues.insert(std::pair<Command, int>{Command::w, SDL_SCANCODE_W});
	m_SDLCommandValues.insert(std::pair<Command, int>{Command::x, SDL_SCANCODE_X});
	m_SDLCommandValues.insert(std::pair<Command, int>{Command::y, SDL_SCANCODE_Y});
	m_SDLCommandValues.insert(std::pair<Command, int>{Command::z, SDL_SCANCODE_Z});

	m_SDLCommandValues.insert(std::pair<Command, int>{Command::leftShift, SDL_SCANCODE_LSHIFT});
	m_SDLCommandValues.insert(std::pair<Command, int>{Command::leftCtrl, SDL_SCANCODE_LCTRL});
	m_SDLCommandValues.insert(std::pair<Command, int>{Command::tab, SDL_SCANCODE_TAB});
	m_SDLCommandValues.insert(std::pair<Command, int>{Command::rightCtrl, SDL_SCANCODE_RCTRL});
	m_SDLCommandValues.insert(std::pair<Command, int>{Command::rightShift, SDL_SCANCODE_RSHIFT});
	m_SDLCommandValues.insert(std::pair<Command, int>{Command::enter, SDL_SCANCODE_RETURN});
	m_SDLCommandValues.insert(std::pair<Command, int>{Command::backspace, SDL_SCANCODE_BACKSPACE});
	m_SDLCommandValues.insert(std::pair<Command, int>{Command::space, SDL_SCANCODE_SPACE});
	m_SDLCommandValues.insert(std::pair<Command, int>{Command::esc, SDL_SCANCODE_ESCAPE});

	m_SDLCommandValues.insert(std::pair<Command, int>{Command::one, SDL_SCANCODE_1});
	m_SDLCommandValues.insert(std::pair<Command, int>{Command::two, SDL_SCANCODE_2});
	m_SDLCommandValues.insert(std::pair<Command, int>{Command::three, SDL_SCANCODE_3});
	m_SDLCommandValues.insert(std::pair<Command, int>{Command::four, SDL_SCANCODE_4});
	m_SDLCommandValues.insert(std::pair<Command, int>{Command::five, SDL_SCANCODE_5});
	m_SDLCommandValues.insert(std::pair<Command, int>{Command::six, SDL_SCANCODE_6});
	m_SDLCommandValues.insert(std::pair<Command, int>{Command::seven, SDL_SCANCODE_7});
	m_SDLCommandValues.insert(std::pair<Command, int>{Command::eight, SDL_SCANCODE_8});
	m_SDLCommandValues.insert(std::pair<Command, int>{Command::nine, SDL_SCANCODE_9});
	m_SDLCommandValues.insert(std::pair<Command, int>{Command::zero, SDL_SCANCODE_0});

	m_SDLCommandValues.insert(std::pair<Command, int>{Command::left, SDL_SCANCODE_LEFT});
	m_SDLCommandValues.insert(std::pair<Command, int>{Command::right, SDL_SCANCODE_RIGHT});
	m_SDLCommandValues.insert(std::pair<Command, int>{Command::down, SDL_SCANCODE_DOWN});
	m_SDLCommandValues.insert(std::pair<Command, int>{Command::up, SDL_SCANCODE_UP});

	m_SDLCommandValues.insert(std::pair<Command, int>{Command::leftMouseButton, SDL_BUTTON_LEFT});
	m_SDLCommandValues.insert(std::pair<Command, int>{Command::rightMouseButton, SDL_BUTTON_RIGHT});
	m_SDLCommandValues.insert(std::pair<Command, int>{Command::middleMouseButton, SDL_BUTTON_MIDDLE});
	m_SDLCommandValues.insert(std::pair<Command, int>{Command::scrollWheel, SDL_BUTTON_MIDDLE});
}

bool SDLInputService::IsButtonPressed(const Command command,const int value)
{
	if (command == Command::leftMouseButton || command == Command::rightMouseButton || command == Command::middleMouseButton)
	{
		//MOUSE
		int x{};
		int y{};
		if (SDL_GetMouseState(&x, &y) & SDL_BUTTON(value))
		{
			return true;
		}
	}
	if (command == Command::scrollWheel)
	{
		//ScrolWheel
	}
	
	//KEYBOARD
	const auto& pStates = SDL_GetKeyboardState(nullptr);
	if (pStates[value])
		return true;
	
	
	return false;
}
