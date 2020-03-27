#pragma once
#include <iostream>
#include <fstream>
#include <string>

using namespace std;
class InputReader
{

private:
	wstring path{};
	wifstream input{};
public:
	InputReader() = delete;
	InputReader(wstring pathway) : path(pathway) {
		input.open(path);
	}
	~InputReader() {
		input.close();
	}

	wstring readFile();

};

