#pragma once
namespace Crusade
{
	class CrusadeGame;
	class GameLoop
	{
	public:
		explicit GameLoop(CrusadeGame* game);
		~GameLoop();

		GameLoop(const GameLoop& other) = delete;
		GameLoop(GameLoop&& other) = delete;
		GameLoop& operator=(const GameLoop& other) = delete;
		GameLoop& operator=(GameLoop&& other) = delete;

		void Run();
	
	private:
		void Init();
		void Exit();
		CrusadeGame* m_Game;
	};
}
