#ifndef __MEMORYMGMT_HPP_
#define __MEMORYMGMT_HPP_
#include "../utils/multiboot_info.hpp"
#define MEM_PAGE_DETAILS_SIZE 1024

struct MemoryPageDetails {
    bool allocated = false;
    void* startAddress = 0x0;
    unsigned long length = 0x0;
};

class MemoryMgmt {
public:
    static MemoryPageDetails memoryPages[MEM_PAGE_DETAILS_SIZE];
    static MemoryPageDetails allocateMemory(unsigned long length);
    static void deallocateMemory(MemoryPageDetails mpd);
    static void deallocateMemory(void* mpd);
    static void init(multiboot_info_t* mbi);
private:
    static multiboot_info_t* mbi;
    static MemoryPageDetails* getFirstEmptyPage(unsigned long minLength);
};

#endif