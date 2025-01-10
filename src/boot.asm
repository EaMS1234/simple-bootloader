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
mov al, 20 ; big number for testing only, change later
call read_disk

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

read_disk:
    mov ah, 0x02
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
    jc sector_error

    ret

sector_error:
    ; Try reading the sectors again, but this time, it will try reading only
    ; the sectors that are actually available
    mov ax, dx
    ret

[bits 32]
protected_mode:
    mov ax, data_segment
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ebp, 0x90000
    mov esp, ebp

    jmp kernel

; Fills the rest of the sector with zeroes
times 510 - ($-$$) db 0

; Adds a word containing the BIOS' Magic Number in the end
dw 0xaa55
