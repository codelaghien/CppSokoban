#pragma once
using namespace std;
#include <iostream>
#include <windows.h>
#include <string>
#include <codecvt>
#include <locale>
#include <conio.h>   
#include <vector>
#include <fstream> 
 
using namespace std; 

class HuyIO
{ 
	public:
		HuyIO();
		~HuyIO();

		static vector<wstring> loadGame(string fileName);
};

