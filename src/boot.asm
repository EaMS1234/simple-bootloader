; Real mode
[bits 16]

; Tells the assembler where to load the bootloader instructions in memory
[org 0x7c00]

; Saves disk as a variable
disk equ 0
mov [disk], dl

; Saves the address of the code and data segments as variables
code_segment equ code_descriptor - gdt
data_segment equ data_descriptor - gdt

; 4 kb kernel offset
kernel equ 0x1000

; Sets the stack up
mov bp, 0x9000
mov sp, bp

; Reads the disk, and saves the data on the kernel address
mov ah, 0x02
mov al, 55
mov ch, 0
mov cl, 2
mov dh, 0
mov dl, [disk]
mov bx, kernel
push ax
int 0x13

; Verifies if all expected sectors could be read
pop dx
cmp al, dl
jc disk_error

; Text mode clears the screen
mov ah, 0x0
mov al, 0x3
int 0x10

; Disables bios interruptions
cli

; Loads the GDT
lgdt [gdt_descriptor]

; Changes the last bit in CR0 to 1 
mov eax, cr0
or eax, 1
mov cr0, eax

; Jumps into the 32 bit section
jmp code_segment:protected_mode

; Infinite loop to keep the CPU running
jmp $

; Global Descriptor Table (Flat model) ---
gdt:
    null_descriptor:
        ; 8 empty bytes
        dd 0
        dd 0
    
    code_descriptor:
        ; Segment limit (16 bit)
        dw 0xffff

        ; Base's first 24 bits
        dw 0
        db 0

        ; Present, Privilege, Type = 1001 + flags = 1010
        db 0b10011010

        ; Other flags + last four bits (1s)
        db 0b11001111

        ; base last 8 bits
        db 0
    
    data_descriptor:
        dw 0xffff
        dw 0
        db 0

        ; Present, Privilege, Type = 1001 + flags = 0010
        db 0b10010010

        ; Other flags + last four bits (1s)
        db 0b11001111

        db 0
    
gdt_end:

gdt_descriptor:
    ; gdt size
    dw gdt_end - gdt - 1
    
    ; gdt start
    dd gdt

disk_error:
    mov ah, 0x0e
    mov al, [kernel]
    int 0x10
    jmp $

[bits 32]
protected_mode:
    ; TESTING - Prints the character # in white by writing directly over video memory
    mov al, '#'
    mov ah, 0x0f
    mov [0xb8000], ax
    jmp $

; Fills the rest of the sector with zeroes
times 510 - ($-$$) db 0

; Adds a word containing the BIOS' Magic Number in the end
dw 0xaa55

; TESTING - writes an entire sector with data to be read by the bootloader
times 512 db 'E'
