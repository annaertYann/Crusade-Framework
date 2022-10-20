#pragma once
#include <string>
namespace Crusade
{
	enum class ButtonType
	{
		down,
		pressed,
		released
	};

	enum class InputCommandType
	{
		button,
		axis
	};
	enum class Command
	{
		a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z,
		leftMouseButton,rightMouseButton,middleMouseButton,scrollWheel,
		leftShift,leftCtrl,tab,rightCtrl,rightShift,enter,backspace,space,esc,
		one,two,three,four,five,six,seven,eight,nine,zero,
		left,right,up,down
	};
	struct InputCommand
	{
		explicit InputCommand(const InputCommandType commandType, const std::string& name, const Command positiveButton, const Command negativeButton, const ButtonType buttonType)
			:name(name)
			, positiveButton(positiveButton)
			, negativeButton(negativeButton)
			, commandType(commandType)
			, axisValue()
			, buttonType(buttonType)
		{}
		explicit InputCommand(const InputCommandType commandType, const std::string& name, const Command positiveButton, const Command negativeButton)
			:name(name)
			, positiveButton(positiveButton)
			, negativeButton(negativeButton)
			, commandType(commandType)
			, axisValue()
			, buttonType(ButtonType::pressed)
		{}
		std::string name;
		Command positiveButton;
		Command negativeButton;
		InputCommandType commandType;
		float axisValue;
		bool active=false;
		bool isDown=false;
		ButtonType buttonType;
	};
}
