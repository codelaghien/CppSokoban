#pragma once
using namespace std;
#include <iostream>
#include <windows.h>
#include <string>
#include <codecvt>
#include <locale>
#include <conio.h>   
#include <vector>
   
#include "HuyWindows.h" 
#include "HuyColors.h" 
#include "HuySize.h" 
#include "HuyCurrentConsole.h"
#include "HuyIO.h" 
#include "HuyGame.h"  
#include "HuyConfig.h"
#include "HuyCommon.h"

class HuyCore
{

	private: 
		HuyWindows _HuyWindows;
		vector<HuyGame> _HuyGames;
		HuyWindows _Legends;
		bool _Legends_Opened;
		int _CurrentGame; 
		int _CellWidth = 5;
		int _CellHeight = 3;
		enum class Direction { UP, RIGHT, BOTTOM, LEFT };

	public: 
		HuyCore(const wstring title, int backgroundColor = 0, int foregroundColor = 7);
		~HuyCore();

		void intro();
		void help();
		void run();
		void runRandom(int no); 
		bool doMove(Direction direction);
		void drawBlock(int left, int top, int row, int column, wchar_t ch, bool countBoxes = false);
		void drawLegends(); 
		void printBottomCommands();
		void alert(wstring title, wstring messages[], int size, bool info = true, string position = "center", int closeTime = 3);
		void byeBye();
};

