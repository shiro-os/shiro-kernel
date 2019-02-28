#!/bin/bash

printf "Started build!\n\n"

printf "Creating binary folder...\n"
mkdir -p ./bin


# Compile kernel/kernel.c
# -c  = Compile without Linking
# -Os = Optimize for Space
# -o  = Set Output-File
rm ./bin/kernel.bin
gcc ./kernel/kernel.c -c -Os -o ./bin/kernel.o
objcopy -O binary ./bin/kernel.o ./bin/kernel.bin -j .text
rm ./bin/kernel.o

printf "Compiling boot sector NASM...\n"
nasm -f bin ./bootsector/bootsector_main.asm -o ./bin/boot_sector.bin

rm ./bin/boot.bin
cat ./bin/boot_sector.bin ./bin/kernel.bin >> ./bin/boot.bin

printf "Launching Kernel...\n"
qemu-system-x86_64 -fda ./bin/boot.bin -boot c

exit 0
