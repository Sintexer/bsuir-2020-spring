#include <iostream>
#include <windowsx.h>
#include <Windows.h>
#include <stdio.h>

using namespace std;
void* Malloc(size_t size);
void Free(void* ptr);


int main() {

	char* str = (char*)Malloc(20);
	
	cout << "Input char array" << endl;

	gets_s(str, 20);
	puts(str);

	Free(str);
}

void* Malloc(size_t size)												//Allocates the specified number of bytes from the heap
{
	void* pointer;
	HLOCAL memoryHandle;												//A handle to a local memory block
	memoryHandle = LocalAlloc(LMEM_MOVEABLE, size + sizeof(HLOCAL));	//(uFlags, uBytes)
	if (!memoryHandle)  throw bad_alloc();

	pointer = LocalLock(memoryHandle);									//Locks a local memory object and returns a pointer to the first byte of the object's memory block
	pointer = (char*)pointer + sizeof(HLOCAL);							//Skip HLOCAL struct
	return pointer;

}

void Free(void* pointer)
{
	HLOCAL memoryHandle;
	memoryHandle = (char*)pointer - sizeof(HLOCAL);

	LocalUnlock(memoryHandle);
	if (LocalFree(memoryHandle)) {
		cout << "Memory free failed" << GetLastError() << endl;
		throw bad_alloc();
	}
}