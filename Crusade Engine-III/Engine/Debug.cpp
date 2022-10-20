#include "Debug.h"
#include "iostream"
using namespace Crusade;
void Debug::Print(const std::string& message)
{
	std::cout << message << std::endl;
}
void Debug::Print(const float& message)
{
	std::cout << message << std::endl;
}
void Debug::Print(const int& message)
{
	std::cout << message << std::endl;
}

void Debug::Print(const Vector2f& message)
{
	std::cout << message.x << ", " << message.y << std::endl;
}

void Debug::Print(const Point2f& message)
{
	std::cout << message.x << ", " << message.y << std::endl;
}

void Debug::Print(const Circlef& message)
{
	std::cout <<"Center: "<< message.center.x << ", " << message.center.y << "; Radius: " << message.radius << std::endl;
}

void Debug::Print(const Rectf& message)
{
	std::cout << "left: " << message.left << " , bottom: " << message.bottom << " , width: " << message.width << " , Height: " << message.height << std::endl;
}
