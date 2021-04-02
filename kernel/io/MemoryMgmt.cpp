#include "MemoryMgmt.hpp"
#include "../utils/util.hpp"
#include "../utils/kernelutils.hpp"

multiboot_info_t* MemoryMgmt::mbi;
MemoryPageDetails MemoryMgmt::memoryPages[MEM_PAGE_DETAILS_SIZE];

void * operator new(unsigned int size)
{
    return MemoryMgmt::allocateMemory(size).startAddress;
}

void * operator new[](unsigned int size)
{
    return MemoryMgmt::allocateMemory(size).startAddress;
}

void operator delete[](void * p)
{
    MemoryMgmt::deallocateMemory(p);
}

void operator delete(void * p)
{
    MemoryMgmt::deallocateMemory(p);
}

void operator delete(void * p, unsigned int size)
{
    MemoryMgmt::deallocateMemory(p);
}

void MemoryMgmt::init(multiboot_info_t* mbi) {
    MemoryMgmt::mbi = mbi;
    MemoryMgmt::memoryPages[0].startAddress = (void*)mbi->mem_lower;
}

MemoryPageDetails MemoryMgmt::allocateMemory(unsigned long length) {
    MemoryPageDetails* mpd = MemoryMgmt::getFistEmptyPage(length);
    if(mpd == 0) {
        kernel_panic("Failed to find empty memory page");
    }
    if(mpd->startAddress == 0) {
        MemoryPageDetails lastDetails;
        for(int i = 0; i < MEM_PAGE_DETAILS_SIZE; i++) {
            MemoryPageDetails pageDetails = MemoryMgmt::memoryPages[i];
            if(pageDetails.startAddress == 0) break;
            if(pageDetails.startAddress > lastDetails.startAddress) {
                lastDetails = pageDetails;
            }
        }
        mpd->startAddress = lastDetails.startAddress + lastDetails.length;
    }
    mpd->length = length;
    mpd->allocated = true;
    return *mpd;
}

MemoryPageDetails* MemoryMgmt::getFistEmptyPage(unsigned long minLength) {
    for(int i = 0; i < MEM_PAGE_DETAILS_SIZE; i++) {
        MemoryPageDetails pageDetails = MemoryMgmt::memoryPages[i];
        if(!pageDetails.allocated && (pageDetails.length == 0 || pageDetails.length >= minLength)) {
            return (MemoryPageDetails*) (MemoryMgmt::memoryPages + i);
        }
    }
    return 0;
}

void MemoryMgmt::deallocateMemory(MemoryPageDetails mpd) {
    if(mpd.startAddress == 0x00) return;
    memfill(mpd.startAddress, 0x00, mpd.length);
    MemoryMgmt::deallocateMemory(mpd.startAddress);
}

void MemoryMgmt::deallocateMemory(void* mpd) {
    if(mpd == 0x00) return;

    for(int i = 0; i < MEM_PAGE_DETAILS_SIZE; i++) {
        if(MemoryMgmt::memoryPages[i].startAddress == mpd) {
            MemoryMgmt::memoryPages[i].allocated = false;
            return;
        }
    }
}
