#include "MemMng.h"


void Mm::MmFree(Page *page, int dwSize)
{
	VirtualFree(this->Location, this->dwSize, MEM_DECOMMIT | MEM_RELEASE);
	SecureZeroMemory(this->Location, this->dwSize);
}

void Mm::MmAlloc(Page *page,int dwSize)
{
	if (dwSize > 0 || dwSize < page->dwPage) {
		if (page->dwPage - MmCheck(page) > dwSize) {
			this->Location = VirtualAlloc(page->nextAddr, dwSize, MEM_COMMIT, PAGE_READWRITE);
			this->dwSize = dwSize;
		}
	}
}

void Mm::MmReAlloc(Page *page, int dwSize)
{
	if (MmCheck(page) > dwSize) {
		if (this->dwSize > 0) {
			this->dwSize = dwSize;
			this->Location = VirtualAlloc(page->nextAddr, this->dwSize, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
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
	SYSTEM_INFO	sysInfo = { NULL };
	GetSystemInfo(&sysInfo);
	this->pPage = new BYTE[sysInfo.dwPageSize];
	this->dwPage = sysInfo.dwPageSize;
	this->nextAddr = this->pPage;
	SecureZeroMemory(&sysInfo, sizeof(SYSTEM_INFO));
}
