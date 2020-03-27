#include <iostream>
#include <string>
#include <Windows.h>
#include <locale>
#include "InputReader.h"

int main(void) {
	using namespace std;
	setlocale(LC_ALL, "Rus");
	wstring file;
	InputReader reader(L"input.txt");
	file = reader.readFile();
	wofstream outf(L"output.txt");
	outf << file;
	outf.close();
	return 0;
}