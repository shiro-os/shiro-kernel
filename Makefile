cppOutput = ./bin/kernel/sources/kernel.o \
		./bin/kernel/sources/io/Terminal.o \
		./bin/kernel/sources/utils/util.o \
		./bin/kernel/sources/utils/kernelutils.o \
		./bin/kernel/sources/utils/string.o \
		./bin/kernel/sources/utils/gdt.o \
		./bin/kernel/sources/io/PortIo.o \
		./bin/kernel/sources/io/SerialIo.o \
		./bin/kernel/sources/io/RTC.o \
		./bin/kernel/sources/io/MemoryMgmt.o \
		./bin/kernel/sources/io/hid/PSController.o \
		./bin/kernel/sources/io/hid/Keyboard.o \
		./bin/kernel/sources/io/hid/layouts/IKeyboardLayout.o \
		./bin/kernel/sources/io/hid/layouts/GermanKeyboardLayout.o \
		./bin/kernel/sources/shells/ComShell.o \
		./bin/kernel/sources/shells/ShellCommandExecutor.o \
		./bin/kernel/sources/test/assert.o \
		./bin/kernel/sources/test/test.o \
		./bin/kernel/sources/interrupts/idt.o \
		./bin/kernel/sources/interrupts/irq_handler.o \
		./bin/kernel/sources/interrupts/interrupt_utils.o \
		./bin/kernel/sources/ui/TuiObject.o \
		./bin/kernel/sources/ui/TuiContainer.o

cOutput = ./bin/kernel/sources/utils/math.o

asmOutput = ./bin/kernel/sources/kernel_ep.oasm \
	./bin/kernel/sources/utils/util.oasm \
	./bin/kernel/sources/interrupts/idt.oasm



all: afterBuild ./bin/shiro.iso

isodir:
	rm -rf ./isodir
	mkdir ./isodir
	mkdir ./isodir/boot
	mkdir ./isodir/boot/grub

$(cppOutput):
	mkdir -p $(@D)
	g++ -g -m32 -c "$(@:bin/%.o=%.cpp)" -o "$@" -ffreestanding -fno-exceptions -fno-rtti -finline-functions -Ikernel/headers/

$(cOutput):
	mkdir -p $(@D)
	g++ -g -m32 -c "$(@:bin/%.o=%.c)" -o "$@" -ffreestanding -fno-exceptions -fno-rtti -finline-functions -Ikernel/headers/

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
	rm -rf ./bin/sources
	rm -rf ./isodir
