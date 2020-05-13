#include <windows.h>
#include <iostream>
#include <stdio.h>
#include <list>
#include "ThreadLib.h"

using namespace std;

int main() {
	char* buffer = (char*)calloc(bsize, sizeof(char));
	HANDLE event = CreateEvent(NULL, false, false, L"event");

	HANDLE reader = CreateThread(NULL, 0, inThread, buffer, 0, NULL);
	HANDLE writer = CreateThread(NULL, 0, outThread, buffer, 0, NULL);
	WaitForSingleObject(reader, INFINITE);
	CloseHandle(reader);
	WaitForSingleObject(writer, INFINITE);
	CloseHandle(writer);
	CloseHandle(event);
}