#pragma once
#include <string>
#include "GeneralStucts.h"
namespace Crusade
{
	class Debug final
	{
	public:
		Debug() = delete;
		~Debug() = delete;
		
		Debug(const Debug& other) = delete;
		Debug(Debug&& other) = delete;
		Debug& operator=(const Debug& other) = delete;
		Debug& operator=(Debug&& other) = delete;
		
		static void Print(const std::string& message);
		static void Print(const Vector2f& message);
		static void Print(const Point2f& message);
		static void Print(const Rectf& message);
		static void Print(const Circlef& message);
		static void Print(const int& message);
		static void Print(const float& message);
	};
}
