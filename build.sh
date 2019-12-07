#!/bin/bash
function cleanup() {
    printf "\e[33m (Re)creating binary folder \e[0m\n"
    rm -r ./bin
    mkdir -p ./bin
}

function compileKernel() {
    printf "\e[33m Compiling Kernel... [step: kernel.c] \e[0m\n"
    g++ ./kernel/kernel.c -ffreestanding -c -o ./bin/kernel.o
    printf "\e[1;33m Compiling Kernel... [step: ld; offset: 0x1000] \e[0m\n"
    ld -Ttext 0x1000 ./bin/kernel.o -o ./bin/kernel.bin --oformat binary
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
    printf "\e[33m Launching Bootloader... \e[0m\n"
    qemu-system-x86_64 -fda ./bin/boot.bin -boot c
}


printf "Started build!\n\n"

cleanup
compileKernel
compileBootsector
createImage
launch

exit 0