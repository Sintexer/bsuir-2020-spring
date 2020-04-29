#include "pch.h"
#include "ByteCounter.h"

map<wchar_t, int>& ByteCounter::add(wstring info) {
	for (wchar_t a : info) {
		if (catalog.find(a) != catalog.end())
			++catalog[a];
		else
			catalog[a] = 1;
	}
	return catalog;
}

map<wchar_t, int>& ByteCounter::getCatalog() {
	return catalog;
}