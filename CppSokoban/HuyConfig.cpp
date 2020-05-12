#include "HuyConfig.h"  

HuyConfig::HuyConfig() {
}

HuyConfig::~HuyConfig() {
}
 
bool HuyConfig::loadGame(vector<HuyGame>& games) {
	vector<wstring> data = HuyIO::loadGame("Rdlom.txt");  // Roger Delaporte
	//vector<wstring> data = HuyIO::loadGame("696.txt"); // Dries de Clercq
	int totalGames = 0;
	int maxWidth = 0;
	int maxHeight = 0;
	int skip = 0;
	for (int i = 0; i < data.size(); i++) {
		wstring line = data[i];
		if (line != L"") {
			int index = line.find(L";");
			if (index >= 0) {
				HuyGame game;
				game.setName(MyCommon::trim(line.substr(1)));
				game.MaxWidth = maxWidth;
				game.MaxHeight = maxHeight;  
				vector<wstring> gameData(data.begin() + (i - maxHeight), data.begin() + (i - maxHeight) + maxHeight);
				game.Data = gameData;
				game.setAuthor(L"Roger Delaporte"); // "Rdlom.txt"
				//game.setAuthor(L"Dries de Clercq"); // "696.txt" 
				games.push_back(game);
				totalGames++;
				maxWidth = 0;
				maxHeight = 0;
				skip++;
			}
			else {
				if (maxWidth < line.size()) maxWidth = line.size(); 
				maxHeight++;
			} 
		}
		else {
			skip++;
		}
	}
	return true;
}
 