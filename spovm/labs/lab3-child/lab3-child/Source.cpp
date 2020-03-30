#include <conio.h>
#include <windows.h>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <limits>
#include <string.h>


const int sMax = 2;
using namespace std;

int main() {

	HANDLE hSemaphore = OpenSemaphoreA
	(
		SEMAPHORE_ALL_ACCESS,		// атрибут доступа
		FALSE,		// инициализированное начальное состояние счетчика
		"semaphore"	// имя объекта
	);


	HANDLE hPipe;
	LPCWSTR pipeName = L"\\\\.\\pipe\\infoPipe";

	hPipe = CreateFile(pipeName, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);

	char* message = new char[256];
	DWORD readc;
	Sleep(100);

	while (true) {
		WaitForSingleObject(hSemaphore, INFINITE);
		ReadFile(hPipe, message, 256, &readc, NULL);
		if (strcmp(message, "q")==0) {
			ReleaseSemaphore(hSemaphore, 1, NULL);
			CloseHandle(hPipe);
			CloseHandle(hSemaphore);
		}
		else {
			break;
			cout << "Recieved message:" << endl << message;
			ReleaseSemaphore(hSemaphore, 1, NULL);
		}
	}
	return 0;
}	