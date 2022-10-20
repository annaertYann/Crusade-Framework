#include "Engine/GameLoop.h"
#include "Game.h"

int main(int, char* [])
{
	GameLoop loop{ new Game() };
	loop.Run();
	return 0;
}
