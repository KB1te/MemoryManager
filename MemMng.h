#pragma once
#include <iostream>
#include <Windows.h>

class Page;

struct Mm {
	
	void	MmFree(Page* page, int dwSize);
	void	MmAlloc(Page *page, int dwSize);
	void	MmReAlloc(Page *page, int dwSize);
	LPVOID	GetLocationPtr();
	int	MmCheck(Page *page);

private:
	LPVOID	Location;
	int	dwSize;
};


class Page{
public:
	void	CreatePage();
	LPVOID	pPage;
	LPVOID	nextAddr;
	int	dwPage;
};


