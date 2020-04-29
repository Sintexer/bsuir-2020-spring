#include "pch.h"
#include "Tree.h"
#include "InputReader.h"
#include "ByteCounter.h"


int main(void) {
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	setlocale(0, "Rus");
	wstring file;
	InputReader reader(L"input.txt");
	wofstream outf(L"output.txt");
	file = reader.readFile();
	ByteCounter byteCounter(file);
	map<wchar_t, int> cat = byteCounter.getCatalog();
	file.clear();
	for (map<wchar_t, int>::iterator it = cat.begin(); it != cat.end(); ++it) {
		//outf << (*it).first << ":" << (*it).second << endl;
		wstring temp;
		temp += (const wchar_t)(*it).first;
		temp+= L":" + to_wstring((*it).second) + L"\n";
		///temp.append((*it).first);
		wcout << temp;
		file.append(temp);
	}
	outf << file;

	outf.close();
	return 0;
}