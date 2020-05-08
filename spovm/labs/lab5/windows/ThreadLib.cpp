#include "pch.h"
#include "ThreadLib.h"

void fillZero(char* str, int sz) {
	for (int i = 0; i < sz; ++i) {
		str[i] = 0;
	}
}

DWORD WINAPI inThread(LPVOID buffer) {
	using namespace std;
	list<const TCHAR*> files;
	files.push_back(L"input1.txt");
	files.push_back(L"input2.txt");
	files.push_back(L"input3.txt");

	//TCHAR filename[bsize] = L"input.txt";
	HANDLE event = OpenEvent(EVENT_ALL_ACCESS, false, L"event");
	OVERLAPPED io;
	io.Offset = 0;
	io.OffsetHigh = 0;
	io.hEvent = event;
	while (!files.empty()) {
		fillZero((char*)buffer, bsize);
		HANDLE hIn = CreateFile(
			files.front(),
			GENERIC_READ,
			0,
			NULL,
			OPEN_EXISTING,
			FILE_FLAG_OVERLAPPED,
			&io
		);
		cout << hIn << endl;
		DWORD bReaden;
		ReadFile(
			hIn,
			buffer,
			GetFileSize(hIn, NULL),
			&bReaden,
			&io
		);
		CloseHandle(hIn);
		//SetEvent(event);
		files.pop_front();
		if (files.empty())
			break;
		Sleep(100);
		WaitForSingleObject(event, INFINITE);
	}
	canLeave = true;

	return 0;
}

DWORD WINAPI outThread(LPVOID buffer) {
	using namespace std;
	HANDLE event = OpenEvent(EVENT_ALL_ACCESS, false, L"event");
	OVERLAPPED io;
	io.Offset = 0;
	io.OffsetHigh = 0;
	io.hEvent = event;
	HANDLE hOut = CreateFile(
		L"output.txt",
		GENERIC_WRITE,
		0,
		NULL,
		CREATE_ALWAYS,
		FILE_FLAG_OVERLAPPED,
		&io
	);

	while (!canLeave) {
		cout << "waiting" << endl;
		WaitForSingleObject(event, INFINITE);

		cout << "awaited" << endl;
		int len = strlen((char*)buffer);
		WriteFile(
			hOut,
			buffer,
			len,
			NULL,
			&io
		);
		io.Offset += len;
		//SetEvent(event);
		Sleep(100);
	}
	CloseHandle(hOut);
	return 0;
}