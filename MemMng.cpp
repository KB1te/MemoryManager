#include "MemMng.h"


void MmInfo::MmFree(Mm *page, int dwSize)
{
	VirtualFree(this->Location, this->dwSize, MEM_DECOMMIT | MEM_RELEASE);
	SecureZeroMemory(this->Location, this->dwSize);
}

void MmInfo::MmAlloc(Mm *page,int dwSize)
{

	if (MmCheck(page) > dwSize) {
		this->Location = VirtualAlloc(page->nextAddr, dwSize, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
		this->dwSize = dwSize;
	}

	
}

void MmInfo::MmReAlloc(Mm *page, int dwSize)
{
	if (MmCheck(page) > dwSize) {
		if (this->dwSize > 0) {
			VirtualFree(this->Location, this->dwSize, MEM_DECOMMIT | MEM_RELEASE);
			this->dwSize = dwSize;
			MmCheck(page);
			VirtualAlloc(page->nextAddr, this->dwSize, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
		}
	}
}

void MmInfo::MmRead(Mm *page, int dwSize,void* buff)
{
	if (sizeof(buff) == this->dwSize) {
		
		for (int i = 0; i < this->dwSize; i++) {
			buff = this->Location;
		}
		
	}
	
}

int MmInfo::MmCheck(Mm *page)
{
	int empty = 0;
	int filled = 0;

	DWORD read = (DWORD)page->pPage;

	for (int i = 0; i < page->dwPage; i++) {
		if (read++ == NULL) {
			empty++;
		}
		else {
			filled++;
		}
	}
	page->nextAddr = reinterpret_cast<LPVOID>((DWORD)page->pPage + filled);
	return empty;
}


inline void MmInfo::MmWrite(Mm *page, int dwSize,void* buff)
{
	if (sizeof(buff) == this->dwSize) {
		for (int i = 0; i < this->dwSize; i++) {
			this->Location = buff;
		}
	}

}


MmInfo *Mm::CreatePage()
{
	SYSTEM_INFO		sysInfo;
	SecureZeroMemory(&sysInfo, sizeof(SYSTEM_INFO));
	GetSystemInfo(&sysInfo);
	this->pPage = VirtualAlloc(NULL, sysInfo.dwPageSize, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
	this->dwPage = sysInfo.dwPageSize;
	SecureZeroMemory(&sysInfo, sizeof(SYSTEM_INFO));
	return &MmInfo();
}
