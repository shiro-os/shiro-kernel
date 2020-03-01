#!/bin/bash
function cleanup() {
    printf "\e[33m (Re)creating binary folder \e[0m\n"
    rm -r ./bin
    mkdir -p ./bin
}

function compileKernel() {
    printf "\e[33m Compiling Kernel... [step: compiling; file: kernel_ep.asm] \e[0m\n"
    # -f: Format, compile as elf64 image so we can merge the header with our C Kernel
    nasm -f elf32 ./kernel/kernel_ep.asm -o./bin/kernel_ep.elf.bin
    printf "\e[33m Compiling Kernel... [step: compiling; file: kernel.c] \e[0m\n"
    # -ffreestanding: Don't link standard library
    # -m64: Compile as 64bit image
    # -O0: Disable all Optimizations
    # -c: Don't Link
    gcc ./kernel/kernel.c -ffreestanding -O0 -m32 -c -o./bin/kernel.o -fno-pie
    printf "\e[33m Compiling Kernel... [step: compiling; file: math.c] \e[0m\n"
    gcc ./kernel/math.c -ffreestanding -O0 -m32 -c -o./bin/math.o -fno-pie
    printf "\e[33m Compiling Kernel... [step: compiling; file: util.c] \e[0m\n"
    gcc ./kernel/util.c -ffreestanding -O0 -m32 -c -o./bin/util.o -fno-pie
    printf "\e[33m Compiling Kernel... [step: compiling; file: condraw.c] \e[0m\n"
    gcc ./kernel/condraw.c -ffreestanding -O0 -m32 -c -o./bin/condraw.o -fno-pie
    printf "\e[33m Compiling Kernel... [step: linking] \e[0m\n"
    # -nostdlib: Don't include stdlib
    # -nodefaultlib: Skip default libs
    # -T link.ld: Run Linkerscript 'link.ld'
    ld -m elf_i386 -nostdlib -nodefaultlibs -T link.ld ./bin/kernel_ep.elf.bin ./bin/kernel.o ./bin/math.o ./bin/util.o ./bin/condraw.o -o./bin/kernel.bin
}

function compileBootsector() {
    printf "\e[33m Compiling boot sector NASM...\e[0m\n"
    nasm -fbin ./bootsector/bootsector_main.asm -o./bin/boot_sector.bin
}

function createImage() {
    printf "\e[33m Creating image... \e[0m\n"
    cat ./bin/kernel.bin >> ./bin/boot.bin
}

function launch() {
    printf "\e[33m Launching VM... \e[0m\n"
    qemu-system-i386 -kernel ./bin/kernel.bin
}


printf "Started build!\n\n"

cleanup
compileKernel
#compileBootsector
createImage
launch

exit 0
