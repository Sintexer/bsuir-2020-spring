#include <iostream>
#include <windowsx.h>
#include <Windows.h>
#include <stdio.h>
#include <list>

struct BytesBlock {
	void* adress;
	long size;
};

const char memSize = 64;

using namespace std;
void* Malloc(size_t size);
bool Free(void* ptr);
void* FindBlock(long size);
void FillBlock(BytesBlock bb, int mark);
bool FreeBlock(void* ptr);
void MoveBlocks();

static char Memory[memSize];
list<BytesBlock> blocks;
list<char**> pointers;

int main() {

	char* p1 = (char*)Malloc(5);
	char* p2 = (char*)Malloc(10);
	char* p3 = (char*)Malloc(10);
	char* p4 = (char*)Malloc(12);
	char* p5 = (char*)Malloc(10);
	pointers.push_back(&p1);
	pointers.push_back(&p2);
	pointers.push_back(&p3);
	pointers.push_back(&p4);
	pointers.push_back(&p5);
	printf("Memory: %d\n", &Memory);
	printf("p1: %d\n", p1);
	printf("p2: %d\n", p2);
	printf("p3: %d\n", p3);
	printf("p4: %d\n", p4);
	printf("p5: %d\n\nAfter:\n", p5);

	Free(p1);
	Free(p3);
	MoveBlocks();

	char* p6 = (char*)Malloc(10);
	pointers.push_back(&p6);
	printf("Memory: %d\n", &Memory);
	printf("p2: %d\n", p2);
	printf("p4: %d\n", p4);
	printf("p5: %d\n", p5);
	printf("p6: %d\n", p6);
	Free(p2);
	Free(p4);
	Free(p5);
	Free(p6);
}

void FillBlock(BytesBlock bb, int mark) {
	char* p = (char*)bb.adress;
	for (int i = 0; i < bb.size; ++i)
		p[i] = (char)mark;
}

bool FreeBlock(void* ptr) {
	if (!blocks.size())
		return false;
	list<BytesBlock>::iterator it;
	for (it = blocks.begin(); it != blocks.end(); ++it) {
		if ((*it).adress == ptr)
			break;
	}
	if (it == blocks.end())
		return false;
	list<char**>::iterator pit;
	for (pit = pointers.begin(); pit != pointers.end(); ++pit) {
		if (**pit == ptr)
			break;
	}
	if (pit == pointers.end())
		throw bad_alloc();
	FillBlock(*it, 0);
	blocks.erase(it);
	pointers.erase(pit);
	return true;
}

void* FindBlock(long size) {
	if (size > memSize)
		return nullptr;
	for (int i = 0; i < memSize - size; ++i) {
		bool isFree = true;
		for (int k = 0; k < size; ++k) {
			if (Memory[i + k]) {
				isFree = false;
				i += k;
				break;
			}
		}
		if (isFree) {
			return (void*)&Memory[i];
		}
	}
	return nullptr;
}

void* Malloc(size_t sz)												//Allocates the specified number of bytes from the Memory
{
	void* pointer;
	pointer = FindBlock(sz);
	if (!pointer)
		return nullptr;
	BytesBlock bb{ pointer, sz };
	blocks.push_back(bb);
	FillBlock(bb, 1);
	return pointer;
}

bool Free(void* pointer)
{
	return FreeBlock(pointer);
}

void MoveBlocks() {
	char* p = (char*)&Memory;
	char* temp = nullptr;
	int i = 0;
	int count{};
	bool first = true;
	while (i < memSize) {
		if (!p[i]) {
			++count;
			if (first) {
				temp = &Memory[i];
				first = false;
			}
		}
		else if (count) {
			list<BytesBlock>::iterator it;
			for (it = blocks.begin(); it != blocks.end(); ++it) {
				if ((*it).adress == temp + count)
					break;
			}
			if (it == blocks.end())
				throw bad_alloc();
			list<char**>::iterator pit;
			for (pit = pointers.begin(); pit != pointers.end(); ++pit) {
				if (**pit == temp + count)
					break;
			}
			if (pit == pointers.end())
				throw bad_alloc();
			**pit = temp;
			FillBlock(*it, 0);
			(*it).adress = temp;
			FillBlock(*it, 1);
			first = true;
			i += (*it).size - count;
			count = 0;
			continue;
		}
		++i;
	}
}