#pragma once
#include <string>
namespace Crusade
{
	struct Window
	{
		explicit Window(const std::string& title = "Title", float width = 320.0f, float height = 180.0f, bool isVSyncOn = true)
			:title{ title }
			, width{ width }
			, height{ height }
			, isVSyncOn{ isVSyncOn }
		{}
		std::string title;
		float width;
		float height;
		bool isVSyncOn;
	};
}
