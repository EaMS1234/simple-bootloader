all: boot.bin

boot.bin:
	nasm -f bin src/boot.asm -o boot.bin
