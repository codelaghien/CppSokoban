#pragma once
using namespace std;
#include "HuyCommon.h"
#include "HuyIO.h" 
#include "HuyGame.h"  

class HuyConfig
{
	public:
		HuyConfig();
		~HuyConfig();
	 
		static bool loadGame(vector<HuyGame>& games); 
};

