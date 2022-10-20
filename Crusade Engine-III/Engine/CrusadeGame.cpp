#include "CrusadeGame.h"
#include "SceneManager.h"
using namespace Crusade;
CrusadeGame::CrusadeGame()
{
}

CrusadeGame::~CrusadeGame()
{
	
}

void CrusadeGame::Tick() const
{
	SceneManager::GetInstance().Tick();
}

void CrusadeGame::LoadScene(const std::string& name)
{
	SceneManager::GetInstance().LoadScene(name);
}


