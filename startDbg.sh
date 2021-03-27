#!/bin/bash
nohup qemu-system-i386 \
    -m 1024 \
    -cdrom ./bin/shiro.iso -s -S \
& gdb -s ./bin/shiro.bin \
    -ex "target remote localhost:1234" \
    -ex "layout next" \
    -ex "layout next" \
    -ex "layout next" \
    --nx
