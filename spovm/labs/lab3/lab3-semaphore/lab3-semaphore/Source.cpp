#include <conio.h>
#include <windows.h>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <limits>
#include <string.h>

const int buffSize = 256;
using namespace std;

int main() {

	HANDLE hSemaphore = CreateSemaphoreA
	(
		NULL,		// атрибут доступа
		1,			// инициализированное начальное состояние счетчика
	    1,			// максимальное количество обращений
		"semaphore"	// имя семафора
	);

	HANDLE hPipe;
	LPCWSTR pipeName = L"\\\\.\\pipe\\infoPipe";

	hPipe = CreateNamedPipe(
		pipeName,
		PIPE_ACCESS_DUPLEX,
		PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
		2,
		512, 512, NULL, NULL);

	

	STARTUPINFO si;
	ZeroMemory(&si, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);
	PROCESS_INFORMATION pi;

	string message;
	DWORD written;
	WaitForSingleObject(hSemaphore, INFINITE);
	if (!CreateProcess(L"D:\\Repositories\\2020-spring\\spovm\\labs\\lab3\\lab3-child\\Debug\\lab3-child.exe",
		NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi)) {
		cout << "Create Process failed" << GetLastError() << endl;
		system("pause");
		exit(EXIT_FAILURE);
	}
	if (!ConnectNamedPipe(hPipe, NULL)) {
		cerr << "Error connecting pipe" << endl;
		return 1;
	}
	cout << "Parent window. Print \"q\" for exit" << endl;
	while (true) {
		cout << "Input message:" << endl;
		getline(cin, message);
		if (message != "q") {
			WriteFile(hPipe, message.c_str(), buffSize, &written, NULL);
			ReleaseSemaphore(hSemaphore, 1, NULL);
			WaitForSingleObject(hSemaphore, INFINITE);
		}
		else {
			WriteFile(hPipe, message.c_str(), buffSize, &written, NULL);
			ReleaseSemaphore(hSemaphore, 1, NULL);
			WaitForSingleObject(hSemaphore, INFINITE);
			DisconnectNamedPipe(hPipe);
			CloseHandle(pi.hThread);
			CloseHandle(pi.hProcess);
			CloseHandle(hPipe);
			CloseHandle(hSemaphore);
			break;
		}
	}
	return 0;
}