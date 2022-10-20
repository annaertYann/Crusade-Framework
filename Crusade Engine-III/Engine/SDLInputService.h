#pragma once
#include "InputService.h"
#include "SDL_events.h"
#include <map>
namespace Crusade
{
	class SDLInputService final : public InputService
	{
	public:
		explicit SDLInputService(const std::vector<InputCommand>& commandList);
		bool ProcessInput() override;
	private:
		void CreateCommandValues();
		static bool IsButtonPressed(Command command,int value);
		void ProcessAxis( InputCommand& command);
		void ProcessButton( InputCommand& command);
		SDL_Event m_E;
		std::map<Command, int> m_SDLCommandValues;
	};
}
