#include "pch.h"
#include "InputReader.h"

wstring InputReader::readFile() {
	{
		input.seekg(0, ios::end);
		size_t size = input.tellg();
		wstring temp(size, ' ');
		input.seekg(0);
		input.read(&temp[0], size);
		return temp;
	}
}