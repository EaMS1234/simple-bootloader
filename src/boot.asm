; Real mode
[bits 16]

; Tells the assembler where to load the bootloader instructions in memory
[org 0x7c00]

; Saves disk as a variable
disk equ 0
mov [disk], dl

mov ah, 0x0e
mov al, '!'
int 0x10

; 4 kb kernel offset
kernel equ 0x1000

; TESTING - Reads the disk, and saves the data on it from 0x7e00 onwards
mov ah, 0x02
mov al, 1
mov ch, 0
mov cl, 2
mov dh, 0
mov dl, [disk]
mov bx, 0x7e00
int 0x13

; Prints the character at 0x7e00
mov ah, 0x0e
mov al, [0x7e00]
int 0x10

; Infinite loop to keep the CPU running
jmp $

; Fills the rest of the sector with zeroes
times 510 - ($-$$) db 0

; Adds a word containing the BIOS' Magic Number in the end
dw 0xaa55

; TESTING - writes an entire sector with data to be read by the bootloader
times 512 db 'g'
