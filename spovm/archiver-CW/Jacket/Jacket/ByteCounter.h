#pragma once
#include "pch.h"

class ByteCounter
{
private:
	map<wchar_t, int> catalog;
public:
	ByteCounter() {}
	ByteCounter(wstring info){
		add(info);
	}

	map<wchar_t, int>& add(wstring info);
	map<wchar_t, int>& getCatalog();
};

