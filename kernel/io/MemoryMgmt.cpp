#include "MemoryMgmt.hpp"
#include "../utils/util.hpp"

multiboot_info_t* MemoryMgmt::mbi;
MemoryPageDetails MemoryMgmt::memoryPages[MEM_PAGE_DETAILS_SIZE];

void MemoryMgmt::init(multiboot_info_t* mbi) {
    MemoryMgmt::mbi = mbi;
    MemoryMgmt::memoryPages[0].startAddress = (void*)mbi->mem_lower;
}

MemoryPageDetails MemoryMgmt::allocateMemory(unsigned long length) {
    MemoryPageDetails* mpd = MemoryMgmt::getFistEmptyPage(length);
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
        if(pageDetails.startAddress == 0 && (pageDetails.length == 0 || pageDetails.length >= minLength)) {
            return (MemoryPageDetails*) ((void*)MemoryMgmt::memoryPages + sizeof(MemoryPageDetails)*i);
        }
    }
}

void MemoryMgmt::deallocateMemory(MemoryPageDetails mpd) {
    if(mpd.startAddress == 0x00) return;

    for(int i = 0; i < MEM_PAGE_DETAILS_SIZE; i++) {
        if(MemoryMgmt::memoryPages[i].startAddress == mpd.startAddress) {
            MemoryMgmt::memoryPages[i].allocated = false;
        }
    }
}
