#include <Windows.h>
#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <list>
#include <iterator>

using namespace std;

CRITICAL_SECTION critsec;
list<DWORD> to_close;
vector<HANDLE> events;
size_t current;
bool close = 0;

void outStrByChar(wstring& str) {
	for (auto a : str) {
		wcout << a;
		Sleep(50);
	}
	cout << endl;
}

DWORD WINAPI ThreadFunc(LPVOID ThreadParam) {
	wstring info = L"Thread ";
	DWORD number = *(DWORD*)ThreadParam;
	HANDLE event = OpenEvent(EVENT_ALL_ACCESS, false, to_wstring(number).c_str());
	HANDLE se = OpenEvent(EVENT_ALL_ACCESS, false, L"syncr");
	*(DWORD*)ThreadParam = *(DWORD*)ThreadParam+1;
	SetEvent(se);
	info += to_wstring(number);
	while (true) {
		WaitForSingleObject(event, INFINITE);
		if (close)
			return 0;
		EnterCriticalSection(&critsec);
		if(to_close.size())
		if (GetCurrentThreadId() == to_close.front()) {
			to_close.pop_front();
			ResetEvent(events.back());
			events.pop_back();
			if (events.size()) {
				current = 0;
				HANDLE tmp = events[current];
				SetEvent(tmp);
			}
			LeaveCriticalSection(&critsec);
			return 0;
		}

		for (auto a : info) {
			wcout << a;
			Sleep(20);
		}
		cout << endl;
		++current;
		if (current == events.size())
			current = 0;
		LeaveCriticalSection(&critsec);
		HANDLE tmp = events[current];
		SetEvent(tmp);
	}
	return 0;
}



HANDLE CreateNewThread(DWORD* number) {
	DWORD dwThreadId;
	HANDLE hThread;
	hThread = CreateThread(
		NULL,
		0,
		ThreadFunc,
		number,
		0,
		&dwThreadId
	);
	return hThread;
}


int main() {
	DWORD number = 0;
	vector<HANDLE> thrIds;
	char input;
	HANDLE se = CreateEvent(NULL, false, false, L"syncr");
	InitializeCriticalSection(&critsec);
	cout << "Input +, - or q:" << endl;
	while (true) {
		cin >> input;
		switch (input)
		{
		case '+': {
			
			thrIds.push_back(CreateNewThread(&number));
			events.push_back(CreateEvent(NULL, false, false, to_wstring(number).c_str()));
			WaitForSingleObject(se, INFINITE);
			if (events.size() == 1) {
				HANDLE tmp = events.front();
				SetEvent(tmp);
			}
			break;
		}
		case '-': {
			if (thrIds.empty()) {
				cout << "No more threads left" << endl;
			}
			else {
				HANDLE tmp1 = thrIds.back(), tmp2 = events.back();
				thrIds.pop_back();
				to_close.push_back(GetThreadId(tmp1));
				WaitForSingleObject(tmp1, INFINITE);
				CloseHandle(tmp1);
				CloseHandle(tmp2);
				
			}
			break;
		}
		case 'q': {
			close = true;
			while (!thrIds.empty()) {
				HANDLE tmp1 = thrIds.back(), tmp2 = events.back();
				thrIds.pop_back();
				events.pop_back();
				CloseHandle(tmp1);
				CloseHandle(tmp2);
			}

			exit(0);
		}
		default:
			break;
		}
	}
	return 0;
}