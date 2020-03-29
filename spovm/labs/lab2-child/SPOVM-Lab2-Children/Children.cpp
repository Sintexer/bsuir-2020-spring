#include <iostream>
#include <Windows.h>

using namespace std;

int main(int argc, char** argv) {

	HANDLE awaker = OpenEvent(EVENT_ALL_ACCESS, false, L"awaker");

	string description = argv[0];
	description = "process " + description;
	while (true) {
		WaitForSingleObject(awaker, INFINITE);
		for (int i = 0; i < description.length(); ++i)
			cout << description[i];
		cout << endl;
		Sleep(500);
		SetEvent(awaker);	
	}


	return 0;
}