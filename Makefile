cppOutput = ./bin/kernel/kernel.o \
		./bin/kernel/io/Terminal.o \
		./bin/kernel/utils/util.o \
		./bin/kernel/utils/kernelutils.o \
		./bin/kernel/utils/string.o \
		./bin/kernel/utils/gdt.o \
		./bin/kernel/io/PortIo.o \
		./bin/kernel/io/SerialIo.o \
		./bin/kernel/shells/ComShell.o \
		./bin/kernel/shells/ShellCommandExecutor.o \
		./bin/kernel/test/assert.o \
		./bin/kernel/test/test.o \
		./bin/kernel/interrupts/idt.o \
		./bin/kernel/interrupts/irq_handler.o \
		./bin/kernel/interrupts/interrupt_utils.o

cOutput = ./bin/kernel/utils/math.o

asmOutput = ./bin/kernel/kernel_ep.oasm \
	./bin/kernel/utils/util.oasm \
	./bin/kernel/interrupts/idt.oasm



all: afterBuild ./bin/shiro.iso

isodir:
	rm -rf ./isodir
	mkdir ./isodir
	mkdir ./isodir/boot
	mkdir ./isodir/boot/grub

$(cppOutput):
	mkdir -p $(@D)
	g++ -g -m32 -c "$(@:bin/%.o=%.cpp)" -o "$@" -ffreestanding -fno-exceptions -fno-rtti -finline-functions

$(cOutput):
	mkdir -p $(@D)
	g++ -g -m32 -c "$(@:bin/%.o=%.c)" -o "$@" -ffreestanding -fno-exceptions -fno-rtti -finline-functions

$(asmOutput):
	mkdir -p $(@D)
	nasm -f elf32 "$(@:bin/%.oasm=%.asm)" -o "$@"

./bin/shiro.bin: $(cppOutput) $(cOutput) $(asmOutput)
	gcc -g -m32 $^ -T link.ld -o$@ -nostdlib -nodefaultlibs

./bin/shiro.iso: ./bin/shiro.bin isodir
	cp -p ./bin/shiro.bin ./isodir/boot/shiro.bin
	cp -p ./cfg/grub.cfg ./isodir/boot/grub/grub.cfg
	grub-mkrescue -o ./bin/shiro.iso ./isodir > /dev/null

afterBuild: ./bin/shiro.iso
	rm -rf ./bin/kernel
	rm -rf ./bin/shiro.bin
	rm -rf ./isodir
