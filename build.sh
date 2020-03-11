#!/bin/bash
set -e
function cleanup() {
    printf "\e[33m (Re)creating binary folder \e[0m\n"
    rm -r ./bin
    mkdir -p ./bin
    rm -r ./isodir
    mkdir -p ./isodir/boot/grub
}

CROSS_COMPILER_PATH=$(which i686-elf-g++)

function compileKernel() {
    set -e
    printf "\e[33m Compiling Kernel... [step: compiling; file: kernel_ep.asm] \e[0m\n"
    # -f: Format, compile as elf64 image so we can merge the header with our C Kernel
    nasm -f elf32  ./kernel/kernel_ep.asm -o ./bin/boot.o
    
    if [ -x "$CROSS_COMPILER_PATH" ]; then
        printf "\e[33m Detected Cross Compiler... going forward with i686-elf-g++ \e[0m\n"
        printf "\e[33m Building File for Shiro: kernel.cpp... \e[0m\n"
        i686-elf-g++ -c ./kernel/kernel.cpp -o ./bin/kernel.o -ffreestanding -fno-exceptions -fno-rtti
        printf "\e[33m Building File for Shiro: Terminal.cpp... \e[0m\n"
        i686-elf-g++ -c ./kernel/Terminal.cpp -o ./bin/Terminal.o -ffreestanding -fno-exceptions -fno-rtti
    else
        printf "\e[33m Missing correct Cross compiler... Fallback to g++ (May cause unwanted behaviour) \e[0m\n"
        printf "\e[33m Building File: kernel.cpp... \e[0m\n"
        g++ -m32 -c ./kernel/kernel.cpp -o ./bin/kernel.o -ffreestanding -fno-exceptions -fno-rtti
    fi

    printf "\e[33m Linking binaries... \e[0m\n"
    if [ -x "$CROSS_COMPILER_PATH" ]; then
        i686-elf-gcc ./bin/boot.o ./bin/kernel.o ./bin/Terminal.o -T link.ld -o./bin/shiro.bin -nostdlib -nodefaultlibs -lgcc
    else
        gcc -m32 ./bin/boot.o ./bin/kernel.o ./bin/Terminal.o -T link.ld -o./bin/shiro.bin -nostdlib -nodefaultlibs
    fi
}

function checkMultiboot() {
    set -e
    printf "\e[33m Check if Kernel is still Multibootable... \e[0m\n"
    grub-file --is-x86-multiboot ./bin/shiro.bin
}

function createImage() {
    set -e
    printf "\e[33m Creating image... \e[0m\n"
    cp -p ./bin/shiro.bin ./isodir/boot/shiro.bin
    cp -p ./cfg/grub.cfg ./isodir/boot/grub/grub.cfg
    grub-mkrescue -o ./bin/shiro.iso ./isodir > /dev/null 2>&1
}

function launch() {
    printf "\e[33m Launching VM... \e[0m\n"
    qemu-system-i386 -cdrom ./bin/shiro.iso
}


printf "Started build!\n\n"

cleanup
compileKernel
#compileBootsector
checkMultiboot
createImage
launch

exit 0
