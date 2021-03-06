#ifndef __KERNELUTILS_HPP_
#define __KERNELUTILS_HPP_
#define DISABLE_PROTECTED_MODE __asm("sti\n\r" "push %eax\n\r" "mov %eax, %cr0\n\r" "and %eax, 0xFFFFFFFE\n\r" "mov %cr0, %eax\n\r" "pop %eax\n\r" "ljmp $0x8, $.ku_dpm\n\r" ".ku_dpm:\n\r");
#define ENABLE_PROTECTED_MODE __asm("cli\n\r" "push %eax\n\r" "mov %eax, %cr0\n\r" "or %eax, 1\n\r" "mov %cr0, %eax\n\r" "pop %eax\n\r" "ljmp $0x8, $.ku_epm\n\r" ".ku_epm:\n\r");

extern "C" void disable_interrupts();
extern "C" void enable_interrupts();

void kernel_panic(const char* errmsg);

void enable_interrupt(unsigned char interrupt);
void disable_interrupt(unsigned char interrupt);


#endif
