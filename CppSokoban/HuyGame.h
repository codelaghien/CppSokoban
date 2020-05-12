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
#include "HuyColors.h"

class HuyGame
{
	private:
		wstring _Author;
		wstring _Name;

	public:
		HuyGame();
		HuyGame(wstring author, wstring name);
		~HuyGame();

		vector<wstring> Data;
		int MaxWidth = 0;
	    int MaxHeight = 0;
		int Person_X = 0;
		int Person_Y = 0;
		int Boxes = 0;
		int Targets = 0;

		void setAuthor(wstring author) { _Author = author; }
		void setName(wstring name) { _Name = name; }
		wstring getAuthor() { return _Author; }
		wstring getName() { return _Name; }

		static wchar_t Wall_Sign;
		static wchar_t Box_Sign;
		static wchar_t BoxOnTarget_Sign;
		static wchar_t Target_Sign; 
		static wchar_t Person_Sign;
		static wchar_t PersonOnTarget_Sign;

		static int Wall[2]; 
		static int Box[2]; 
		static int BoxOnTarget[2]; 
		static int Target[2];  
		static int Person[2]; 
		static int PersonOnTarget[2]; 
};

