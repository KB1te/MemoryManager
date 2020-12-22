#include "MemMng.h"


void Mm::MmFree(Page *page, int dwSize)
{
	VirtualFree(this->Location, this->dwSize, MEM_DECOMMIT | MEM_RELEASE);
	SecureZeroMemory(this->Location, this->dwSize);
}

void Mm::MmAlloc(Page *page,int dwSize)
{
	if (MmCheck(page) < dwSize) {
		VirtualFree(page->nextAddr, dwSize, MEM_DECOMMIT | MEM_RELEASE);
		MmCheck(page);
		this->Location = VirtualAlloc(page->nextAddr, dwSize, MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE);
		this->dwSize = dwSize;
	}	
}

void Mm::MmReAlloc(Page *page, int dwSize)
{
	if (MmCheck(page) > dwSize) {
		if (this->dwSize > 0) {
			VirtualFree(this->Location, this->dwSize, MEM_DECOMMIT | MEM_RELEASE);
			this->dwSize = dwSize;
			MmCheck(page);
			VirtualAlloc(page->nextAddr, this->dwSize, MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE);
		}
	}
}

LPVOID Mm::GetLocationPtr()
{
	return this->Location;
}


int Mm::MmCheck(Page *page){
	int filled = 0;
	DWORD *read = reinterpret_cast<DWORD*>(page->nextAddr);
	for (; *read != NULL; filled++, read++);
	page->nextAddr = read + filled;
	return filled;
}



void Page::CreatePage()
{
	this->pPage = VirtualAlloc(NULL, 16000,MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
	this->dwPage = 16000;
	this->nextAddr = this->pPage;
}
