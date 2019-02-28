#!/bin/bash

printf "Started build!\n\n"

printf "Creating binary folder...\n"
mkdir -p ./bin

### TODO ###
# Compile kernel/kernel.c

printf "Compiling boot sector NASM...\n"
nasm -f bin ./bootsector/bootsector_main.asm -o ./bin/boot_sector.bin

printf "Launching Kernel...\n"
qemu-system-x86_64 -fda ./bin/boot_sector.bin -boot c

exit 0
