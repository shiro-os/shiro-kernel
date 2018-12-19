# Shiro 白~

<p align="center"><img height="150" width="auto" src="http://en.ikanji.jp/user_data/images/upload/character/original/E799BD.png" /></p>
<p align="center"><b>Shiro (白~) - A small, (not yet) monolithic x86 &amp; 64 Kernel</b></p>

## Table of Contents

1. :information_source: [About](#information_source-about)
1. :wrench: [Setup](#wrench-setup)
1. :clipboard: [Documentation](#clipboard-documentation)

<hr>

## :information_source: About

Shiro 白 is a small monolithic x86 &amp; 64 Kernel which is able to process input and provide output accordingly.

The name "Shiro" itself is the Japanese word for "white" written in [Romaji](https://www.japanesepod101.com/japanese-romaji/). The symbol (白) is the japanese [Kanji](https://en.wikipedia.org/wiki/Kanji) for the word "white". 

I wanted to learn a bit about kernel development. And that's basically the whole purpose of this project/repository.

<hr>

## :wrench: Setup

-- Comming Soon --

<hr>

## :clipboard: Documentation

> **Note:** This is _not_ a documentation about the Kernel! This is more like a history of things I did to make everything work. It is basically an explanation of each step I made in the development (this is a good way for me to learn).

My main technologies I use for the development are: 

> - NASM for Bootloader stuff 
> - C for the Kernel itself 
> - Bash for build scripts
> - Qemu as my Type 2 Hypervisor / Emulator 
> - VSCode as my IDE 

- [1.](#doc-1) - **Boot Sector**: <br>
    The first step is to tell the bootloader that Shiro is an OS and that it's bootable. I did this by writing a small NASM code which compiles to a binary.
    - First we create an infinite loop
    - Then we fill the boot sector (512 bytes)
    - And finally end the binary with the 16-Bit magic number `0xAA55`

- [2.](#doc-2) - **Build script**: <br>
    Second step and we already have to write a build script. The boot sector code is written in NASM. So we need to compile a binary out of it first.
    - Create a directory to store our binaries
    - Compile binary with `$ nasm -f bin ./boot_sector.asm -o ./bin/boot_sector.bin`
    - Launch the Kernel with `$ qemu-system-x86_64 ./bin/boot_sector.bin`

<hr>
