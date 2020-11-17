#!/bin/bash
function cleanup() {
    printf "\e[33m (Re)creating binary folder \e[0m\n"
    rm -r ./bin
    mkdir -p ./bin
    rm -r ./isodir
    mkdir -p ./isodir/boot/grub
}

CROSS_COMPILER_PATH=$(which i686-elf-g++)

function compileKernel() {
    toCompile=("./kernel/kernel.cpp" \
    "./kernel/io/Terminal.cpp" \
    "./kernel/utils/math.c" \
    "./kernel/utils/util.cpp" \
    "./kernel/utils/string.cpp" \
    "./kernel/io/PortIo.cpp" \
    "./kernel/io/SerialIo.cpp" \
    "./kernel/shells/ComShell.cpp" \
    "./kernel/shells/ShellCommandExecutor.cpp" \
    "./kernel/test/assert.cpp" \
    "./kernel/test/test.cpp")
    outputs=()
    printf "\e[33m Compiling Kernel... [step: compiling; file: kernel_ep.asm] \e[0m\n"
    # -f: Format, compile as elf64 image so we can merge the header with our C Kernel
    nasm -f elf32  ./kernel/kernel_ep.asm -o ./bin/boot.o

    if [ -x "$CROSS_COMPILER_PATH" ]; then
        printf "\e[33m Detected Cross Compiler... going forward with i686-elf-g++ \e[0m\n"

        for i in "${toCompile[@]}"; do
            printf "\e[33m Building File: $i... \e[0m\n"
            outputName=$(echo "$i" | sed "s/\(.*\)\(\..*\)/\.\/bin\/\1.o/g")
            outputs+=($outputName)
            mkdir -p $(dirname "$outputName")
            i686-elf-g++ -c $i -o $o -ffreestanding -fno-exceptions -fno-rtti
        done
    else
        printf "\e[33m Missing correct Cross compiler... Fallback to g++ (May cause unwanted behaviour) \e[0m\n"

        for i in "${toCompile[@]}"; do
            printf "\e[33m Building File: $i... \e[0m\n"
            outputName=$(echo "$i" | sed "s/\(.*\)\(\..*\)/\.\/bin\/\1.o/g")
            outputs+=($outputName)
            mkdir -p $(dirname "$outputName")
            g++ -g -m32 -c $i -o $outputName -ffreestanding -fno-exceptions -fno-rtti
        done
    fi

    printf "\e[33m Linking binaries... \e[0m\n"
    if [ -x "$CROSS_COMPILER_PATH" ]; then
        i686-elf-gcc ./bin/boot.o ${outputs[@]} -T link.ld -o./bin/shiro.bin -nostdlib -nodefaultlibs -lgcc
    else
        gcc -g -m32 ./bin/boot.o ${outputs[@]} -T link.ld -o./bin/shiro.bin -nostdlib -nodefaultlibs
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

function launchDbg() {
    printf "\e[33m Launching VM in Debug mode... \e[0m\n"
    nohup qemu-system-i386 -m 1024 -cdrom ./bin/shiro.iso -s -S & gdb -s ./bin/shiro.bin -ex "target remote localhost:1234" -ex "layout next" -ex "layout next" -ex "layout next" --nx
}


printf "Started build!\n\n"

cleanup
compileKernel
#compileBootsector
checkMultiboot
createImage
launchDbg

exit 0
