#include "InputService.h"
using namespace Crusade;
InputService::InputService(const std::vector<InputCommand>& commandList)
	:m_InputCommands(commandList)
{
	
}
bool InputService::GetButton(const std::string& name)
{
	for(auto &command : m_InputCommands)
	{
		if(name == command.name)
		{
			return command.active;
		}
	}
	return false;
}

float InputService::GetAxis(const std::string& name)
{
	for (auto& command : m_InputCommands)
	{
		if (name == command.name)
		{
			return command.axisValue;
		}
	}
	return 0;
}
