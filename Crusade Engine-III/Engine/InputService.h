#pragma once
#include <vector>
#include "InputValue.h"
#include "GeneralStucts.h"
#include "Service.h"
namespace Crusade
{
	class InputService : public Service
	{
	public:
		explicit InputService(const std::vector<InputCommand>& commandList);
		virtual ~InputService() = default;

		InputService(const InputService& other) = delete;
		InputService(InputService&& other) = delete;
		InputService& operator=(const InputService& other) = delete;
		InputService& operator=(InputService&& other) = delete;
		
		virtual bool ProcessInput() = 0;
		bool GetButton(const std::string& name);
		float GetAxis(const std::string& name);
		Vector2f GetMousePos()const { return m_MousePos; }
		float GetScrollWheelMotion()const { return m_ScroolWheelMotion; }
	protected:
		std::vector<InputCommand> m_InputCommands;
		Vector2f m_MousePos = Vector2f{};
		float m_ScroolWheelMotion{};
	};
}
