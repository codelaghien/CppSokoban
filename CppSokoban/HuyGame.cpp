#include "HuyGame.h"

HuyGame::HuyGame(): HuyGame(L"", L"") {}
HuyGame::HuyGame(wstring author, wstring name) {
	_Author = author;
	_Name = name;
}
HuyGame::~HuyGame() {

}
 
wchar_t HuyGame::Wall_Sign = L'#';
wchar_t HuyGame::Box_Sign = L'$';
wchar_t HuyGame::BoxOnTarget_Sign = L'*';
wchar_t HuyGame::Target_Sign = L'.'; 
wchar_t HuyGame::Person_Sign = L'@';
wchar_t HuyGame::PersonOnTarget_Sign = L'+';

int HuyGame::Wall[2] = { HuyColors::DARKGRAY, HuyColors::LIGHTGRAY };
int HuyGame::Box[2] = { HuyColors::YELLOW, HuyColors::RED };
int HuyGame::BoxOnTarget[2] = { HuyColors::GREEN, HuyColors::WHITE };
int HuyGame::Target[2] = { HuyColors::BROWN, HuyColors::WHITE };
int HuyGame::Person[2] = { HuyColors::RED, HuyColors::WHITE };
int HuyGame::PersonOnTarget[2] = { HuyColors::GREEN, HuyColors::WHITE };
