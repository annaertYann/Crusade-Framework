#pragma once
#include <string>
#include "GeneralStucts.h"

namespace Crusade
{
	class InputService;
	class Input
	{
	public:
		Input() = delete;
		~Input() = delete;

		Input(const Input& other) = delete;
		Input(Input&& other) = delete;
		Input& operator=(const Input& other) = delete;
		Input& operator=(Input&& other) = delete;

		static bool GetButton(const std::string& name);
		static float GetAxis(const std::string& name);
		static Vector2f GetMousePos();
		static float GetScrollMotion();
	private:
		static InputService* m_Service;
		static void InitService();
	};
}
