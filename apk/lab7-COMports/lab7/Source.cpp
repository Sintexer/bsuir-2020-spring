#include <iostream>
#include "Com.h"
#include <map>
#include <string>
#include <vector>
#include <list>
#include <Windows.h>
using namespace std;

bool checkCombos(char byte, map<vector<int>, int>& combos);
void clearCombos(map<vector<int>, int>& combos);

bool ultraCombo=false;

int main() {
	Com com1("COM1");
	map<vector<int>, int> combos;
	combos[{50, 18, 50}] = 0;
	combos[{35, 18, 46, 37}] = 0;
	combos[{50, 30, 31, 20, 18, 19}] = 0;
	combos[{30, 25, 37}] = 0;
	combos[{31, 38, 30, 47, 18}] = 0;
	char byte{'a'};
	while (com1.isConnected()) {
		com1.read(&byte, 1);
		if (byte != '\0') {
			if (checkCombos(byte, combos)) {
				if (ultraCombo == true) {
					byte = 42;
					ultraCombo = false;
				}
				com1.write(&byte, 1);
			}
		}
		Sleep(100);
	}
	system("pause");
	return 0;
}

bool checkCombos(char byte, map<vector<int>, int>& combos) {
	for (map<vector<int>, int>::iterator it = combos.begin(); it != combos.end(); it++) {
		if (it->first[it->second] == byte)
			++(it->second);
		else
			it->second = 0;
	}
	for (map<vector<int>, int>::iterator it = combos.begin(); it != combos.end(); it++) {
		if (it->first.size() == it->second) {
			clearCombos(combos);
			if (it->first.size() == 6)
				ultraCombo = true;
			return true;
		}
	}
	return false;
}

void clearCombos(map<vector<int>, int>& combos) {
	for (map<vector<int>, int>::iterator it = combos.begin(); it != combos.end(); it++) {
		it->second = 0;
	}
}