#include "HuyCore.h" 

#include <locale>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <conio.h>
#include <windows.h> 
#include <iostream>

HuyCore::HuyCore(const wstring title, int backgroundColor, int foregroundColor) {
	HuySize consoleSize = HuyCurrentConsole::getSize(); 
	_HuyWindows = HuyWindows(0, 0, consoleSize.width, consoleSize.height, 1, backgroundColor, foregroundColor);
	_HuyWindows.showConsoleCursor(false);
	_HuyWindows.clearConsole();
	_HuyWindows.drawFrame();
	_HuyWindows.write(title, (consoleSize.width - title.length()) / 2, 0, HuyColors::RED, HuyColors::WHITE);
	printBottomCommands();

	_Legends = HuyWindows(1, 2, 35, 24, 0, HuyColors::LIGHTBLUE, HuyColors::WHITE);

	HuyConfig::loadGame(_HuyGames);
}
HuyCore::~HuyCore() {
}
void HuyCore::intro() {
	int w = _HuyWindows.getWidth() - 20;
	if (w > 90) w = 90;
	if (w < 90) w = _HuyWindows.getWidth() - 2;
	int h = 29;
	int x = (_HuyWindows.getWidth() - w) / 2;
	int y = (_HuyWindows.getHeight() - h) / 2;

	_HuyWindows.saveScreenRect(x, y, w, h);

	wstring title = L" Giới thiệu tổng quát ";
	int background = HuyColors::LIGHTBLUE;
	int foreground = HuyColors::WHITE;

	_HuyWindows.animateFrame(x, y, w, h, background, foreground);

	HuyWindows introWin(x, y, w, h, 0, background, foreground);
	introWin.clearConsole();
	introWin.drawFrame();
	introWin.write(title, (w - title.length()) / 2, 0, HuyColors::BROWN, foreground);

	foreground = HuyColors::RED;
	int row = 3;
	int col = 4;
	wstring sokoban;
	sokoban = L"███████╗ ██████╗ ██╗  ██╗ ██████╗ ██████╗  █████╗ ███╗   ██╗";
	col = (w - sokoban.length()) / 2; 
	introWin.write(sokoban, col, row++, background, foreground);
	sokoban = L"██╔════╝██╔═══██╗██║ ██╔╝██╔═══██╗██╔══██╗██╔══██╗████╗  ██║";
	introWin.write(sokoban, col, row++, background, foreground);
	sokoban = L"███████╗██║   ██║█████╔╝ ██║   ██║██████╔╝███████║██╔██╗ ██║";
	introWin.write(sokoban, col, row++, background, foreground);
	sokoban = L"╚════██║██║   ██║██╔═██╗ ██║   ██║██╔══██╗██╔══██║██║╚██╗██║";
	introWin.write(sokoban, col, row++, background, foreground);
	sokoban = L"███████║╚██████╔╝██║  ██╗╚██████╔╝██████╔╝██║  ██║██║ ╚████║";
	introWin.write(sokoban, col, row++, background, foreground);
	sokoban = L"╚══════╝ ╚═════╝ ╚═╝  ╚═╝ ╚═════╝ ╚═════╝ ╚═╝  ╚═╝╚═╝  ╚═══╝";
	introWin.write(sokoban, col, row++, background, foreground);

	foreground = HuyColors::WHITE;
	row++;
	col = 4;
	introWin.write(L"Đây là chương trình chơi game Sokoban đơn giản.", col, row++, background, foreground);
	introWin.write(L"Chương trình được viết bằng ngôn ngữ C++.", col, row++, background, foreground);
	row++;
	introWin.write(L"Đây là trò chơi rất được ưa chuộng của Nhật Bản. Ý tưởng của trò chơi là", col, row++, background, foreground);
	introWin.write(L"đẩy mấy thùng hàng trong nhà kho vào đúng chỗ quy định.", col, row++, background, foreground); 
	introWin.write(L"Chỉ đẩy được 1 thùng và không được kéo hay leo qua thùng hàng.", col, row++, background, foreground);
	introWin.write(L"Trò chơi giúp phát triển trí tuệ và tư duy cho các bạn học lập trình !", col, row++, background, foreground);
	row++;
	introWin.write(L"Những thư viện cần để viết là:", col, row++, background, foreground);
	introWin.write(L"+ HuySize:           tự viết đơn giản - giữ tọa độ x, y", col, row++, background, foreground);
	introWin.write(L"+ HuyIO, HuyConfig:  tự viết đơn giản - load games từ text file", col, row++, background, foreground);
	introWin.write(L"+ HuyColors:         tự viết đơn giản - định nghĩa màu", col, row++, background, foreground);
	introWin.write(L"+ HuyCurrentConsole: tự viết đơn giản - lấy thông tin của console", col, row++, background, foreground);
	introWin.write(L"+ HuyWindows:        tự viết đơn giản - vẽ khung, in ra màn hình tại X, Y, ...", col, row++, background, foreground); 
	introWin.write(L"+ HuyCore:           tự viết đơn giản - bộ máy chính", col, row++, background, foreground);
	introWin.write(L"+ HuyGame:           tự viết đơn giản - định nghĩa 1 game", col, row++, background, foreground);
	introWin.write(L"+ ...", col, row++, background, foreground);
	row += 2;
	sokoban = L"Tác giả: Huy Nguyễn";
	introWin.write(sokoban, (w - sokoban.length()) / 2, row++, background, foreground);
	sokoban = L"Năm 2020";
	introWin.write(sokoban, (w - sokoban.length()) / 2, row++, background, foreground);

	wstring close = L" Nhấn phím bất kỳ để đóng ";
	introWin.write(close, (w - close.length()) / 2, h - 1, background, foreground);

	int c = _getch() - 48;
	_HuyWindows.restoreScreenRect();
} 
void HuyCore::help() {
	int w = _HuyWindows.getWidth() - 20;
	if (w > 80) w = 80;
	int h = 17;
	int x = (_HuyWindows.getWidth() - w) / 2;
	int y = (_HuyWindows.getHeight() - h) / 2;
	  
	wstring title = L" Cách chơi Game Sokoban ";
	int background = HuyColors::LIGHTBLUE;
	int foreground = HuyColors::WHITE;
	 
	HuyWindows helpWin(x, y, w, h, 0, background, foreground);

	helpWin.saveScreenRect(0, 0, w, h);
	helpWin.animateFrame(x, y, w, h, background, foreground);

	helpWin.clearConsole();
	helpWin.drawFrame();
	helpWin.write(title, (w - title.length()) / 2, 0, HuyColors::GREEN, foreground);

	int row = 4;
	int col = 4;
	wstring temp = L"Bấm phím mũi tên trái, phải, lên, xuống để di chuyển người chơi ";
	helpWin.write(temp, col, row, background, foreground);
	helpWin.write(L"│ (P) │", col + temp.length(), row++, HuyGame::Person[0], HuyGame::Person[1]);
	temp = L"để đẩy khối vuông ";
	helpWin.write(temp, col, row, background, foreground);
	helpWin.write(L"├─$─┤", col + temp.length(), row, HuyGame::Box[0], HuyGame::Box[1]);
	col += temp.length() + 5;
	temp = L" vào vị trí đích ";
	helpWin.write(temp, col, row, background, foreground);
	helpWin.write(L"│ $$$ │", col + temp.length(), row++, HuyGame::BoxOnTarget[0], HuyGame::BoxOnTarget[1]);

	row++;
	col = 4;
	helpWin.write(L"Luật là:", col, row++, background, foreground);
	temp = L"+ Người chơi chỉ có thể đẩy 1 khối vuông ";
	helpWin.write(temp, col, row, background, foreground);
	helpWin.write(L"├─$─┤", col + temp.length(), row, HuyGame::Box[0], HuyGame::Box[1]);
	helpWin.write(L" đi tới", col + temp.length() + 5, row++, background, foreground);

	temp = L"- Người chơi không thể kéo khối vuông ";
	helpWin.write(temp, col, row, background, foreground);
	helpWin.write(L"├─$─┤", col + temp.length(), row, HuyGame::Box[0], HuyGame::Box[1]);
	helpWin.write(L" lùi lại", col + temp.length() + 5, row++, background, foreground);

	row += 2; 
	temp = L"Tác giả: Huy Nguyễn";
	helpWin.write(temp, (w - temp.length()) / 2, row++, background, foreground);
	temp = L"Năm 2020";
	helpWin.write(temp, (w - temp.length()) / 2, row++, background, foreground);

	wstring close = L" Nhấn phím bất kỳ để đóng ";
	helpWin.write(close, (w - close.length()) / 2, h - 1, background, foreground);

	int c = _getch() - 48;
	helpWin.restoreScreenRect();
}
void HuyCore::run() {
	_CurrentGame = rand() % _HuyGames.size();
	while (_HuyGames[_CurrentGame].MaxHeight * _CellHeight + 6 > _HuyWindows.getHeight()) {
		_CurrentGame = rand() % _HuyGames.size();
	}
	_CurrentGame = 145;
	runRandom(_CurrentGame);

	unsigned int x = _getch();
	while (x != 120) { // x
		switch (x)
		{
			case 110: // n
				_Legends_Opened = false; 
				_CurrentGame = rand() % _HuyGames.size();
				while (_HuyGames[_CurrentGame].MaxHeight * _CellHeight + 6 > _HuyWindows.getHeight()) {
					_CurrentGame = rand() % _HuyGames.size();
				}
				runRandom(_CurrentGame);
				break;
			case 99: // c
				if (_Legends_Opened) {
					_Legends_Opened = false;
					_Legends.restoreScreenRect();
				}
				else {
					_Legends_Opened = true;
					drawLegends();
				}
				break;
			case 114: // r
				if (_Legends_Opened) {
					_Legends_Opened = false;
					_Legends.restoreScreenRect();
				}
				_HuyGames.clear();
				HuyConfig::loadGame(_HuyGames);
				runRandom(_CurrentGame);
				break;
			case 104: // h
				if (_Legends_Opened) {
					_Legends_Opened = false;
					_Legends.restoreScreenRect();
				}
				help();
				break;
			case 75: // left
				if (!doMove(Direction::LEFT)) {
					/*wstring messages[] = { L"Bạn không thể đi qua trái !" };
					alert(L" Thông báo ", messages, 1, false, "bottom", 1);*/
				}
				break;
			case 77: // right
				if (!doMove(Direction::RIGHT)) {
					/*wstring messages[] = { L"Bạn không thể đi qua phải !" };
					alert(L" Thông báo ", messages, 1, false, "bottom", 1);*/
				}
				break;
			case 72: // up
				if (!doMove(Direction::UP)) {
					/*wstring messages[] = { L"Bạn không thể đi lên !" };
					alert(L" Thông báo ", messages, 1, false, "bottom", 1);*/
				}
				break;
			case 80: // bottom
				if (!doMove(Direction::BOTTOM)) {
					/*wstring messages[] = { L"Bạn không thể đi xuống !" };
					alert(L" Thông báo ", messages, 1, false, "bottom", 1);*/
				}
				break;
			default:
				break;
		} 
		x = _getch(); 
	}

	byeBye();
}
void HuyCore::drawLegends() { 
	_Legends.saveScreenRect(0, 0, 35, 24);
	_Legends.animateFrame(1, 2, 35, 24, HuyColors::LIGHTBLUE, HuyColors::WHITE);
	_Legends.clearConsole();
	_Legends.drawFrame();
	int x = 1;
	int y = 3;
	_Legends.write(L" Chú thích ", 11, 0, HuyColors::RED, HuyColors::WHITE);
	drawBlock(x, y, 0, 0, HuyGame::Person_Sign);
	_Legends.write(L"Người chơi", x + _CellWidth + 3, y++, HuyColors::LIGHTBLUE, HuyColors::WHITE);

	y += 2;
	drawBlock(x, y, 0, 0, HuyGame::PersonOnTarget_Sign);
	_Legends.write(L"Người chơi ngay điểm tới", x + _CellWidth + 3, y++, HuyColors::LIGHTBLUE, HuyColors::WHITE);

	y += 2;
	drawBlock(x, y, 0, 0, HuyGame::Wall_Sign);
	_Legends.write(L"Bức tường", x + _CellWidth + 3, y++, HuyColors::LIGHTBLUE, HuyColors::WHITE);

	y += 2;
	drawBlock(x, y, 0, 0, HuyGame::Target_Sign);
	_Legends.write(L"Điểm tới", x + _CellWidth + 3, y++, HuyColors::LIGHTBLUE, HuyColors::WHITE);

	y += 2;
	drawBlock(x, y, 0, 0, HuyGame::BoxOnTarget_Sign);
	_Legends.write(L"Hoàn thành", x + _CellWidth + 3, y++, HuyColors::LIGHTBLUE, HuyColors::WHITE);

	y += 2;
	drawBlock(x, y, 0, 0, HuyGame::Box_Sign);
	_Legends.write(L"Hộp vàng", x + _CellWidth + 3, y++, HuyColors::LIGHTBLUE, HuyColors::WHITE);

	y += 2;
	drawBlock(x, y, 0, 0, L' ');
	_Legends.write(L"Đường đi", x + _CellWidth + 3, y++, HuyColors::LIGHTBLUE, HuyColors::WHITE);

}
void HuyCore::runRandom(int no) {  
	wstring temp = L"Tác giả chế bàn này là: " + _HuyGames[no].getAuthor();
	_HuyWindows.clearConsole();
	_HuyWindows.write(temp, (_HuyWindows.getWidth() - temp.length()) / 2, _HuyWindows.getHeight() - 3, HuyColors::BLUE, HuyColors::WHITE);
	temp = _HuyGames[no].getName();
	_HuyWindows.write(temp, (_HuyWindows.getWidth() - temp.length()) / 2, _HuyWindows.getHeight() - 4, HuyColors::BLUE, HuyColors::WHITE);

	int left = (_HuyWindows.getWidth() - (_HuyGames[no].MaxWidth * _CellWidth)) / 2;
	int top = (_HuyWindows.getHeight() - (_HuyGames[no].MaxHeight * _CellHeight)) / 2 - 2;
	_HuyGames[no].Boxes = 0;
	_HuyGames[no].Targets = 0;
	for (int row = 0; row < _HuyGames[no].Data.size(); row++) {
		bool wall = false;
		int height = _HuyGames[no].Data[row].size();
		for (int col = 0; col < height; col++) {
			if (wall || (_HuyGames[no].Data[row][col] != L' ')) {
				wall = true;
				drawBlock(left, top, row, col, _HuyGames[no].Data[row][col], true);
			}
		}
	} 
}
bool HuyCore::doMove(Direction direction) {
	HuyGame* game = &_HuyGames[_CurrentGame];
	int left = (_HuyWindows.getWidth() - (game->MaxWidth * _CellWidth)) / 2;
	int top = (_HuyWindows.getHeight() - (game->MaxHeight * _CellHeight)) / 2 - 2;
	int x = game->Person_X;
	int y = game->Person_Y;
	int x0 = 0;
	int y0 = 0;
	switch (direction)
	{
		case Direction::UP:
			y0 = -1; 
			break;
		case Direction::RIGHT:
			x0 = 1; 
			break;
		case Direction::BOTTOM:
			y0 = 1; 
			break;
		case Direction::LEFT:
			x0 = -1; 
			break;
		default:
			break;
	}
	bool legalMove = false;
	if (x0 != 0 || y0 != 0) {  
		if (game->Data[y + y0][x + x0] == L' ' || game->Data[y + y0][x + x0] == HuyGame::Target_Sign) {
			game->Data[y][x] = game->Data[y][x] == HuyGame::PersonOnTarget_Sign ? HuyGame::Target_Sign : L' ';
			game->Data[y + y0][x + x0] = game->Data[y + y0][x + x0] == HuyGame::Target_Sign ? HuyGame::PersonOnTarget_Sign : HuyGame::Person_Sign;
			legalMove = true;
		}
		else if ((game->Data[y + y0][x + x0] == HuyGame::Box_Sign || game->Data[y + y0][x + x0] == HuyGame::BoxOnTarget_Sign) && (game->Data[y + y0 * 2][x + x0 * 2] == L' ' || game->Data[y + y0 * 2][x + x0 * 2] == HuyGame::Target_Sign)) {
			game->Data[y][x] = game->Data[y][x] == HuyGame::PersonOnTarget_Sign ? HuyGame::Target_Sign : L' ';
			if (game->Data[y + y0][x + x0] == HuyGame::BoxOnTarget_Sign) game->Targets--;
			game->Data[y + y0][x + x0] = game->Data[y + y0][x + x0] == HuyGame::BoxOnTarget_Sign ? HuyGame::PersonOnTarget_Sign : HuyGame::Person_Sign;
			game->Data[y + y0 * 2][x + x0 * 2] = game->Data[y + y0 * 2][x + x0 * 2] == HuyGame::Target_Sign ? HuyGame::BoxOnTarget_Sign : HuyGame::Box_Sign;
			if (game->Data[y + y0 * 2][x + x0 * 2] == HuyGame::BoxOnTarget_Sign) game->Targets++;
			legalMove = true;
			drawBlock(left, top, y + y0 * 2, x + x0 * 2, game->Data[y + y0 * 2][x + x0 * 2]);
		}
		if (legalMove) {
			game->Person_X += x0;
			game->Person_Y += y0;
			drawBlock(left, top, y, x, game->Data[y][x]);
			drawBlock(left, top, y + y0, x + x0, game->Data[y + y0][x + x0]);
		}
	}
	if (game->Targets == game->Boxes) {
		wstring messages[] = { L"Bạn đã giải xong " + game->getName(), L"Bạn là siêu nhân !" };
		alert(L" Wow, chúc mừng bạn ! ", messages, 2, true, "bottom", 9);
	}
	return legalMove;
}
void HuyCore::drawBlock(int left, int top, int row, int column, wchar_t ch, bool countBoxes) {
	int w = _CellWidth;
	int h = _CellHeight;
	int background = HuyColors::LIGHTCYAN;
	int textcolor = HuyColors::DARKGRAY;
	if (ch == L'#') {
		background = HuyGame::Wall[0]; 
		textcolor = HuyGame::Wall[1];
		HuyWindows block(left + (column * w + 1), top + (row * h + 1), w, h, 0, background, textcolor);

		block.clearConsole(L'░', false);  // ░ ╬ ÷ ≡ ∙
	} else if (ch == HuyGame::Person_Sign) {
		background = HuyGame::Person[0];
		textcolor = HuyGame::Person[1];
		_HuyGames[_CurrentGame].Person_X = column;
		_HuyGames[_CurrentGame].Person_Y = row;
		HuyWindows block(left + (column * w + 1), top + (row * h + 1), w, h, 0, background, textcolor);
		block.clearConsole(' ', false);
		block.drawFrame(); 
		block.write(L"(P)", 1, 1, background, textcolor); 
	}
	else if (ch == HuyGame::PersonOnTarget_Sign) {
		background = HuyGame::PersonOnTarget[0];
		textcolor = HuyGame::PersonOnTarget[1];
		_HuyGames[_CurrentGame].Person_X = column;
		_HuyGames[_CurrentGame].Person_Y = row;
		HuyWindows block(left + (column * w + 1), top + (row * h + 1), w, h, 0, background, textcolor);
		block.clearConsole(' ', false);
		block.drawFrame();
		block.write(L"(P)", 1, 1, background, textcolor);
	}
	else if (ch == HuyGame::Target_Sign) {
		background = HuyGame::Target[0];
		textcolor = HuyGame::Target[1];
		HuyWindows block(left + (column * w + 1), top + (row * h + 1), w, h, 0, background, textcolor);
		block.clearConsole(' ', false);
		block.drawFrame();
		block.write(L"?", 2, 1, background, textcolor);
	}
	else if (ch == HuyGame::Box_Sign) {
		background = HuyGame::Box[0];
		textcolor = HuyGame::Box[1];
		if (countBoxes) _HuyGames[_CurrentGame].Boxes++;
		HuyWindows block(left + (column * w + 1), top + (row * h + 1), w, h, 0, background, textcolor);
		block.clearConsole(' ', false);
		block.drawFrame();
		block.write(L"┬", 2, 0, background, textcolor);
		block.write(L"├─$─┤", 0, 1, background, textcolor);
		block.write(L"┴", 2, 2, background, textcolor);
	}
	else if (ch == HuyGame::BoxOnTarget_Sign) {
		background = HuyGame::BoxOnTarget[0];
		textcolor = HuyGame::BoxOnTarget[1];
		if (countBoxes) { 
			_HuyGames[_CurrentGame].Boxes++;
			_HuyGames[_CurrentGame].Targets++;
		} 
		HuyWindows block(left + (column * w + 1), top + (row * h + 1), w, h, 0, background, textcolor);
		block.clearConsole(' ', false);
		block.drawFrame();
		block.write(L"$$$", 1, 1, background, textcolor);
	}
	else if (ch == L' ') { 
		HuyWindows block(left + (column * w + 1), top + (row * h + 1), w, h, 0, background, textcolor);
		block.clearConsole(L'.', false);
	}
}
void HuyCore::byeBye() {
	int row = (_HuyWindows.getHeight() - 8) / 2;
	_HuyWindows.clearConsole();
	wstring byebye = L"";
	byebye = L"██████╗ ██╗   ██╗███████╗      ██████╗ ██╗   ██╗███████╗";
	int col = (_HuyWindows.getWidth() - byebye.size()) / 2;
	_HuyWindows.write(byebye, col, row++, HuyColors::BLUE, HuyColors::WHITE);
	byebye = L"██╔══██╗╚██╗ ██╔╝██╔════╝      ██╔══██╗╚██╗ ██╔╝██╔════╝";
	_HuyWindows.write(byebye, col, row++, HuyColors::BLUE, HuyColors::WHITE);
	byebye = L"██████╔╝ ╚████╔╝ █████╗        ██████╔╝ ╚████╔╝ █████╗";
	_HuyWindows.write(byebye, col, row++, HuyColors::BLUE, HuyColors::WHITE);
	byebye = L"██╔══██╗  ╚██╔╝  ██╔══╝        ██╔══██╗  ╚██╔╝  ██╔══╝";
	_HuyWindows.write(byebye, col, row++, HuyColors::BLUE, HuyColors::WHITE);
	byebye = L"██████╔╝   ██║   ███████╗      ██████╔╝   ██║   ███████╗";
	_HuyWindows.write(byebye, col, row++, HuyColors::BLUE, HuyColors::WHITE);
	byebye = L"╚═════╝    ╚═╝   ╚══════╝      ╚═════╝    ╚═╝   ╚══════╝";
	_HuyWindows.write(byebye, col, row++, HuyColors::BLUE, HuyColors::WHITE);
	for (int i = 0; i < 5; i++) {
		wstring temp = L" Tự động thoát trong " + to_wstring(5 - i) + L" giây ";
		_HuyWindows.write(temp, (_HuyWindows.getWidth() - temp.size()) / 2, _HuyWindows.getHeight() - 3, HuyColors::LIGHTMAGENTA, HuyColors::WHITE);
		Sleep(1000);
	}
}
void HuyCore::alert(wstring title, wstring messages[], int size, bool info, string position, int closeTime) {
	int w = 50;
	int h = size + 4;
	int x = (_HuyWindows.getWidth() - w) / 2;
	int y = position == "bottom" ? _HuyWindows.getHeight() - h - 2  : (_HuyWindows.getHeight() - h) / 2;

	_HuyWindows.saveScreenRect(x, y, w, h);
	 
	int background = info ? HuyColors::LIGHTMAGENTA : HuyColors::RED;
	int foreground = HuyColors::WHITE;

	_HuyWindows.animateFrame(x, y, w, h, background, foreground);

	HuyWindows infoWin(x, y, w, h, 0, background, foreground);
	infoWin.clearConsole();
	infoWin.drawFrame();
	infoWin.write(title, (w - title.length()) / 2, 0, HuyColors::BROWN, foreground);

	for (int i = 0; i < size; i++) {
		infoWin.write(messages[i], (w - messages[i].length()) / 2, 2 + i, background, foreground);
	}

	wstring temp = L"";
	for (int i = closeTime; i > 0; i--) {
		temp = L" Đóng trong " + to_wstring(i) + L" giây ";
		infoWin.write(temp, (w - temp.length()) / 2, h - 1, HuyColors::BROWN, foreground);
		Sleep(1000);
	}

	_HuyWindows.restoreScreenRect();
}
void HuyCore::printBottomCommands() {
	int col = 1;
	int row = _HuyWindows.getHeight() - 1;
	_HuyWindows.write(L" ", col++, row, HuyColors::BLUE, HuyColors::WHITE);
	wstring temp = L" c ";
	_HuyWindows.write(temp, col, row, HuyColors::GREEN, HuyColors::WHITE);
	col += temp.size();
	temp = L" Xem / đóng chú thích "; 
	_HuyWindows.write(temp, col, row, HuyColors::BLUE, HuyColors::WHITE);

	col += temp.size() + 3;
	_HuyWindows.write(L" ", col++, row, HuyColors::BLUE, HuyColors::WHITE);
	temp = L" h ";
	_HuyWindows.write(temp, col, row, HuyColors::GREEN, HuyColors::WHITE);
	col += temp.size();
	temp = L" Xem cách chơi ";
	_HuyWindows.write(temp, col, row, HuyColors::BLUE, HuyColors::WHITE);

	col += temp.size() + 3;
	_HuyWindows.write(L" ", col++, row, HuyColors::BLUE, HuyColors::WHITE);
	temp = L" n ";
	_HuyWindows.write(temp, col, row, HuyColors::GREEN, HuyColors::WHITE);
	col += temp.size();
	temp = L" Ngẫu nhiên game mới ";
	_HuyWindows.write(temp, col, row, HuyColors::BLUE, HuyColors::WHITE);

	col += temp.size() + 3;
	_HuyWindows.write(L" ", col++, row, HuyColors::BLUE, HuyColors::WHITE);
	temp = L" r ";
	_HuyWindows.write(temp, col, row, HuyColors::GREEN, HuyColors::WHITE);
	col += temp.size();
	temp = L" Reload game ";
	_HuyWindows.write(temp, col, row, HuyColors::BLUE, HuyColors::WHITE);

	col += temp.size() + 3;
	_HuyWindows.write(L" ", col++, row, HuyColors::BLUE, HuyColors::WHITE);
	temp = L" x ";
	_HuyWindows.write(temp, col, row, HuyColors::RED, HuyColors::WHITE);
	col += temp.size();
	temp = L" Thoát ";
	_HuyWindows.write(temp, col, row, HuyColors::BLUE, HuyColors::WHITE);
}
 