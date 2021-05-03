# Shiro 白~

<p align="center"><img height="150" width="auto" src="http://en.ikanji.jp/user_data/images/upload/character/original/E799BD.png" /></p>
<p align="center"><b>Shiro (白~) - A small, (not yet) monolithic x86 &amp; 64 Kernel</b></p>

## Table of Contents

1. :information_source: [About](#information_source-about)
1. :checkered_flag: [Goal](#checkered_flag-goal)
1. :wrench: [Building](#wrench-build)

<hr>

## :information_source: About

Shiro 白 is a small monolithic x86 &amp; 64 Kernel.

The name "Shiro" itself is the Japanese word for "white" written in [Romaji](https://www.japanesepod101.com/japanese-romaji/). The symbol (白) is the japanese [Kanji](https://en.wikipedia.org/wiki/Kanji) for the word "white". 

We want to extend it to a fully functional OS someday.

<hr>

## :checkered_flag: Goal

We want to use as few C++ as possible and bind [v8](https://v8.dev) on Kernel level so that we can programm the entire OS including most parts of the Kernel in JavaScript. We are still debating whether to go with NodeJS, V8 or a [custom fork of v8](https://github.com/shiro-os/v8) to make an ECMAScript compliant JS dialect that has pointers and lowlevel API's.

<hr>

## :wrench: Build

-- Comming Soon --

For now you only need the following tools:

> - NASM for Bootloader stuff 
> - C for the Kernel itself 
> - Bash for build scripts
> - (Recommended:) Qemu as Type 2 Hypervisor / Emulator 

and then build & launch the kernel by starting `build.sh`

<hr>
