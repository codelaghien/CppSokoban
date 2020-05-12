#include "HuyIO.h" 

HuyIO::HuyIO() {

}

HuyIO::~HuyIO() {

} 

vector<wstring> HuyIO::loadGame(string fileName) {
	std::ifstream f(fileName);
	std::wbuffer_convert<std::codecvt_utf8<wchar_t>> conv(f.rdbuf());
	std::wistream wf(&conv); 
	wchar_t str[0x1000]; 
	wchar_t u;
	vector<wstring> result; 
	while (!wf.eof()) {
		wf.getline(str, 1000); 
		result.push_back(str); 
	}
	return result;
} 