#pragma once
#include <windows.h>
#include <string>
#include <iostream>
using namespace std;

class Com
{
	bool connected{};
	HANDLE handle{};
	COMSTAT stat{};
	DWORD errors{};

public:

	Com(string name) {
		handle = CreateFileA(
			name.c_str(),
			GENERIC_READ | GENERIC_WRITE,
			0,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			NULL
		);
		setDefaultSettings();
		connected = true;
		PurgeComm(handle, PURGE_RXCLEAR | PURGE_TXCLEAR);
	}

	~Com() {
		connected = false;
	}

	void setDefaultSettings();
	size_t read(char* buffer, size_t size);
	bool write(char* buffer, size_t size);
	bool isConnected();
};

