#pragma once
#include <iostream>
#include <memory>
#include <Windows.h>

class Mm;

struct MmInfo {
	
	void	MmFree(Mm* page, int dwSize);
	void	MmAlloc(Mm *page, int dwSize);
	void	MmReAlloc(Mm *page, int dwSize);
	void	MmWrite(Mm *page, int dwSize, void* buff);
	void	MmRead(Mm *page, int dwSize, void* buff);
	int		MmCheck(Mm *page);

private:
	LPVOID	Location;
	int		dwSize;
};


class Mm{
public:
	MmInfo	*CreatePage();
	LPVOID	pPage;
	LPVOID	nextAddr;
	int		dwPage;
};


