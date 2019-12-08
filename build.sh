#!/bin/bash
function cleanup() {
    printf "\e[33m (Re)creating binary folder \e[0m\n"
    rm -r ./bin
    mkdir -p ./bin
}

function compileKernel() {
    printf "\e[33m Compiling Kernel... [step: kernel_ep.asm] \e[0m\n"
    nasm -f elf64 ./kernel/kernel_ep.asm -o ./bin/kernel_ep.elf.bin
    printf "\e[33m Compiling Kernel... [step: kernel.c] \e[0m\n"
    gcc ./kernel/kernel.c -ffreestanding -m64 -O0 -c -o ./bin/kernel.o
    printf "\e[33m Compiling Kernel... [step: linking; offset: 0x1000] \e[0m\n"
    ld -nostdlib -nodefaultlibs -Tlink.ld ./bin/kernel_ep.elf.bin ./bin/kernel.o -o./bin/kernel.bin
}

function compileBootsector() {
    printf "\e[33m Compiling boot sector NASM...\e[0m\n"
    nasm -f bin ./bootsector/bootsector_main.asm -o ./bin/boot_sector.bin
}

function createImage() {
    printf "\e[33m Creating image... \e[0m\n"
    cat ./bin/boot_sector.bin ./bin/kernel.bin >> ./bin/boot.bin
}

function launch() {
    printf "\e[33m Launching VM... \e[0m\n"
    qemu-system-x86_64 -fda ./bin/boot.bin -boot c
}


printf "Started build!\n\n"

cleanup
compileKernel
compileBootsector
createImage
launch

exit 0