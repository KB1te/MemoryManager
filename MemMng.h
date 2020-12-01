#pragma once
#include <iostream>
#include <memory>
#include <Windows.h>


struct MmInfo {
	LPVOID	Location;
	int		dwSize;
};

class Mm{
public:
	void MmFree();
	LPVOID	MmAlloc(int dwSize);
	void MmReAlloc(int dwSize);
	void MmWrite(void* buff);
	void MmRead(void* buff);
private:
	MmInfo	 info;
};

