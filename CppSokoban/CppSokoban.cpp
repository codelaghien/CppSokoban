// CppSokoban.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#pragma once

#include <iostream>
#include <conio.h> 
#include <string>
#include <algorithm>
#include <windows.h> 
#include <locale>
#include <codecvt>
#include <cstdlib>
#include <cstdio>  
#include <fstream>      
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */ 

#include "HuySize.h";     
#include "HuyCurrentConsole.h"; 
#include "HuyConfig.h"
#include "HuyCore.h"
#include "HuyWindows.h";  
#include "HuyColors.h";   

using namespace std; 

// https://www.sourcecode.se/sokoban/levels
/*
 #########
 #   #   #
 # @ #   #
##$**$**$#
#  #. .# ##
#  .*$*.  #
#         #
###########
; Two rooms
*/ 

int main()
{
	/* initialize random seed: */
	srand(time(NULL));

	wstring title = L" Chương trình chơi game Sokoban ";

	HuySize consoleSize = HuyCurrentConsole::getSize();
	if (consoleSize.width < 111 || consoleSize.height < 31) {
		HuyWindows win(0, 0, consoleSize.width, consoleSize.height, 1, HuyColors::BLUE, HuyColors::WHITE);
		win.showConsoleCursor(false);
		win.clearConsole();
		win.drawFrame(); 
		win.write(title, (consoleSize.width - title.size()) / 2, 0, HuyColors::RED, HuyColors::WHITE);
		title = L"Nâng kích thước console lên ";
		win.write(title, (consoleSize.width - title.size()) / 2, consoleSize.height / 2 - 1, HuyColors::BLUE, HuyColors::WHITE);
		title = L"Right click -> Properties -> Layout ";
		win.write(title, (consoleSize.width - title.size()) / 2, consoleSize.height / 2, HuyColors::BLUE, HuyColors::WHITE);
		title = L"Screen Buffer Size = Window Size: Width > 111, Height > 30 ";
		win.write(title, (consoleSize.width - title.size()) / 2, consoleSize.height / 2 + 1, HuyColors::BLUE, HuyColors::WHITE);

		unsigned int x = _getch();
	}
	else {
		HuyCore huyCore(title, HuyColors::BLUE, HuyColors::WHITE);
		huyCore.intro();
		huyCore.run(); 
	}

}
 