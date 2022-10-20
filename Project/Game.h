#pragma once
#include "CrusadeEngine.h"
#include "SampleScene.h"
class Game final : public CrusadeGame
{
public:
	
private:
	void Init() override
	{
		CreateScene<SampleScene>("SampleScene");
		LoadScene("SampleScene");
	}
};