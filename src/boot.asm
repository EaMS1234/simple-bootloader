[bits 16]

mov ah, 0x0e
mov al, '!'
int 0x10

times 510 - ($-$$) db 0
dw 0xaa55
