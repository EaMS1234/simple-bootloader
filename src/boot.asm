; Real mode
[bits 16]

; Tells the assembler where to load the bootloader instructions in memory
[org 0x7e00]

mov ah, 0x0e
mov al, '!'
int 0x10

; 4 kb kernel offset
kernel equ 0x1000

; Sets the stack up (64 kb offset)
mov bp, 0x10000
mov sp, bp

; Infinite loop to keep the CPU running
jmp $

; Fills the rest of the sector with zeroes
times 510 - ($-$$) db 0

; Adds a word containing the BIOS' Magic Number in the end
dw 0xaa55
