#include "MemMng.h"


void Mm::MmFree()
{
	VirtualFree(this->info.Location, this->info.dwSize, MEM_DECOMMIT | MEM_RELEASE);
	SecureZeroMemory(this->info.Location, this->info.dwSize);
}

LPVOID Mm::MmAlloc(int dwSize)
{
		
	LPVOID	status;
	status = VirtualAlloc(NULL, dwSize, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

	if (status != NULL) {
		this->info.Location = status;
		this->info.dwSize = dwSize;
		SecureZeroMemory(status, sizeof(dwSize));
		return status;
	}

	return nullptr;
	
}

void Mm::MmReAlloc(int dwSize)
{
	if (this->info.Location != NULL) {
		if (this->info.dwSize > 0) {
			VirtualFree(this->info.Location, this->info.dwSize, MEM_DECOMMIT | MEM_RELEASE);
			this->info.dwSize = dwSize;
			VirtualAlloc(this->info.Location, this->info.dwSize, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
		}
	}
}

void Mm::MmRead(void* buff)
{
	if (sizeof(buff) == this->info.dwSize) {
		
		for (int i = 0; i < this->info.dwSize; i++) {
			buff = this->info.Location;
		}
		
	}
	
}


inline void Mm::MmWrite(void* buff)
{
	if (sizeof(buff) == this->info.dwSize) {
		for (int i = 0; i < this->info.dwSize; i++) {
			this->info.Location = buff;
		}
		
	}

}
