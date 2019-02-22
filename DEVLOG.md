## :clipboard: DevLog

> **Note:** This is _not_ a documentation about the Kernel! This is more like a history of things I did to make everything work. It is basically an explanation of each step I made in the development (this is a good way for me to learn).

My main technologies I use for the development are: 

> - NASM for Bootloader stuff 
> - C for the Kernel itself 
> - Bash for build scripts
> - Qemu as my Type 2 Hypervisor / Emulator 
> - VSCode as my IDE 

<a name="doc-1"></a>
- [1.](#doc-1) - **Boot Sector**: <br>
    The first step is to tell the bootloader that Shiro is an OS and that it's bootable. I did this by writing a small NASM code which compiles to a binary.
    - First we create an infinite loop
    - Then we fill the boot sector (512 bytes)
    - And finally end the binary with the 16-Bit magic number `0xAA55`

    [Show what boot_sector.asm looked like at that time](https://github.com/NLDev/Shiro/blob/27f209a5021869bc94f20d1009bbe37fb0ab098c/boot_sector.asm)

<a name="doc-2"></a>
- [2.](#doc-2) - **Build script**: <br>
    Second step and we already have to write a build script. The boot sector code is written in NASM. So we need to compile a binary out of it first.
    - Create a directory to store our binaries
    - Compile binary with `$ nasm -f bin ./boot_sector.asm -o ./bin/boot_sector.bin`
    - Launch the Kernel with `$ qemu-system-x86_64 ./bin/boot_sector.bin`

    [Show what build.sh looked like at that time](https://github.com/NLDev/Shiro/blob/01659dcd4fb1b45add9aeb3a5ffdbd8263e5cbca/build.sh)

<a name="doc-3"></a>
- [3.](#doc-3) - **Enter TTY Mode in Boot Sector**: <br>
    We will enter TTY mode in the boot sector and output our Kernel name.

    - We use `0x0E` on `ah` to tell the video interrupt that we want to write the content of `al` (lower part of the `ax` register) in TTY mode.

    [Show what boot_sector.asm looked like at that time](https://github.com/NLDev/Shiro/blob/f565a18e994d0c92b0708f12e50313db47016c30/boot_sector.asm)

<a name="doc-4"></a>
- [4.](#doc-4) - **Splitting into functions**: <br>
    No we will try to split our boot sector into multiple functions. For instance we want to have a print function. Some notes:

    - The BIOS places the boot sector at `0x7C00`
    - So `[org 0x7c00]` tells the assembler that our offset is the bootsector code
    - `bx` is our base address for the strings
    - We basically iterate over our string and push each character into the `al` register IF it is not there already
    - We stop once the last character is null
    - We use `bx` as our index pointer (the string is like a char array and bx is our index)
    - `mov al, 0x0a` is a new-line character
    - `mov al, 0x0d` is a carriage return
    - in our bootloader_main.asm file we include subroutines below the hang because we need to make sure the parameters are ready

    [Show what bootsector_main.asm looked like at that time](https://github.com/NLDev/Shiro/blob/4b3756752964452577edd7fce7d14846952a3836/bootsector/bootsector_main.asm)

    [Show what bootsector_print.asm looked like at that time](https://github.com/NLDev/Shiro/blob/4b3756752964452577edd7fce7d14846952a3836/bootsector/bootsector_print.asm)
    
    [Show what build.sh looked like at that time](https://github.com/NLDev/Shiro/blob/4b3756752964452577edd7fce7d14846952a3836/build.sh)

<a name="doc-5"></a>
- [5.](#doc-5) - **Switch to 16Bit Real- and 32Bit protected mode**: <br>
    We will switch to 16bit real mode and then to 32bit protected mode right after. 

    - First we need a couple of helper functions such as an Global Descriptor Table (GDT) and a print function for 32bit
    - We start with printing. This is the first time we need to use 32bit registers. Also we now have protected and virtual memory. However, there are no more BIOS interrupts anymore. Thats why we need a GDT later.
    - We print strings by directly writing to the VGA memory.
    - Printing is almost the same as on interrupts. We iterate over the string and check if we reached the last char (null).
    - Now for the GDT: Segmentation works differently in 32bit. Now, the offset becomes an index to a segment descriptor (SD) in the GDT.
    - I tried to made it as simple as possible and have only two segments: one for the code and one for the data. 
    - There were a couple of oddities that I didn't understand at first:
        - GDT nees to start with 0x00 (null 8-byte or two times 4 bytes in ASM) - apparently to clear the managed addresses (?)
        - We can't directly load the GDT. We need a so called GDT descriptor
    - Basically, for this step I look up all flags in the [os-dev PDF](https://www.cs.bham.ac.uk/~exr/lectures/opsys/10_11/lectures/os-dev.pdf)
    - Now we want to finally switch to 32bit. For that we...
        - Disable interrupts
        - Load our GDT
        - Set a bit on the CPU control register cr0
        - Flush the CPU pipelinewith a far jump
        - Update all the segment registers
        - Update the stack
    - We disable interrupts with `cli`
    - We load our GDT with the GDT descriptor by using `lgdt [gdt_descriptor]`
    - Then we set 32 bit mode in the `cr0` by using `or eax, 0x1`

    [Show what boot_sector.asm looked like at that time](https://github.com/NLDev/Shiro/blob/1b660402f782ff308b6b984ac68374b337e92407/bootsector/bootsector_main.asm)
    
    <hr>
    
