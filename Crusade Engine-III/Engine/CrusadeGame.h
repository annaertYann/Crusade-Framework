#pragma once
#include <string>
#include "SceneManager.h"
namespace Crusade
{
	class CrusadeGame
	{
	public:
		CrusadeGame();
		virtual ~CrusadeGame() ;

		CrusadeGame(const CrusadeGame& other) = delete;
		CrusadeGame(CrusadeGame&& other) = delete;
		CrusadeGame& operator=(const CrusadeGame& other) = delete;
		CrusadeGame& operator=(CrusadeGame&& other) = delete;

		virtual void Tick()const;
		virtual void Init() = 0;

	protected:
		static void LoadScene(const std::string& name);
		template <typename T>
		static void CreateScene(const std::string& name);
	};
	
	template <typename T>
	void CrusadeGame::CreateScene(const std::string& name)
	{
		SceneManager::GetInstance().CreateScene<T>(name);
	}
}