all: build run clean

build:
	nasm -f elf32 src/main_entry.asm -o main_entry.o
	gcc -fno-pie -m32 -ffreestanding -c src/main.c -o main.o
	ld -m elf_i386 -o main.bin -T src/main_entry.ld main_entry.o main.o --oformat binary
	nasm -f bin src/boot.asm -o boot.bin
	cat boot.bin main.bin > disk.bin

run: build
	qemu-system-x86_64 disk.bin

clean:
	rm *.bin
	rm *.o
