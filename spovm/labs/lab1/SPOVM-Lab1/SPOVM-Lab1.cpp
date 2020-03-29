#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <stdio.h>
#include <time.h>

void printTime();

int main() {
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	BOOL bProcess;

	ZeroMemory(&si, sizeof(si));
	ZeroMemory(&pi, sizeof(pi));

	if( !CreateProcess(
		L"D:\\Projects\\Cpp\\SPOVM\\SPOVM-Lab1-Time\\Debug\\SPOVM-Lab1-Time.exe",
		NULL,
		NULL,
		NULL,
		FALSE,
		CREATE_NEW_CONSOLE,
		NULL,
		NULL,
		&si,
		&pi
	)){
		printf("Create Process false\n");
	}
	else {
		printTime();
		printf("Waiting fo child process to close");
		fflush(stdin);
		WaitForSingleObject(pi.hProcess, INFINITE);
		CloseHandle(pi.hThread);
		CloseHandle(pi.hProcess);
	}
}

void printTime() {
	SYSTEMTIME st;
	GetLocalTime(&st);
	printf("%d-%02d-%02d %02d:%02d:%02d.%03d\nParent^^^\n",
		st.wYear,
		st.wMonth,
		st.wDay,
		st.wHour,
		st.wMinute,
		st.wSecond,
		st.wMilliseconds);
}