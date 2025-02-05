#include "io.h"

void print(char * string, int color);
void print_int(int num, int color);
void putchar(char character, int color);
void next_line();
void update_cursor_pos();

int term_x, term_y = 0;

// Prints a string
void print(char * string, int color)
{
    while (*string != 0)
    {
        if (*string == '\n')
        {
            next_line();
            *string++;
        }
        else
        {
            putchar(*string++, color);

            term_x += 1;

            if (term_x >= 80)
            {
                next_line();
            }
        }
    }

    update_cursor_pos();
}

void print_int(int num, int color)
{
    // Represents the divisor for the current operation.
    // It must always be a power of 10.
    int divisor = 1;

    // Checks the maximum number the divisor can be
    while (divisor * 10 <= num)
    {
        divisor = divisor * 10;
    }

    // Decomposes the number and prints on screen
    do
    {
        putchar((char) 48 + (num / divisor), color);
        term_x += 1;

        num = num - divisor * (num / divisor);
        divisor = divisor / 10;
    
        // Prevents not putting the zero after decomposing the number
        if (num == 0 && divisor == 1)
        {
            putchar('0', color);
            term_x += 1;   
        }

    } while (num != 0);

    update_cursor_pos();
}

// Puts a character on the current cursor position
void putchar(char character, int color)
{
    // Writes characters directly into video mode memory space
    char *video = (char*)0xb8000;

    *(video + (term_x * 2) + (term_y * 160)) = character;
    *(video + (term_x * 2) + (term_y * 160) + 1) = color;
}

void next_line()
{
    term_x = 0;
    term_y += 1;    

    update_cursor_pos();
}

// Updates the VGA text mode cursor position by manipulating the values stored
// on some of the internal registers
void update_cursor_pos()
{
    int pos = term_x + (term_y * 80);

    // Sends cursor location low register to the VGA control register
    outb(0x3d4, 0x0f);

    // Transforms pos into binary and uses the data register to change register 0x0f 
	outb(0x3d5, (pos & 0xff));

    // Sends cursor location high register to the VGA control register
    outb(0x3d4, 0x0e);

    // Transforms pos into binary and uses the data to change register 0x0e
    outb(0x3d5, ((pos >> 8) & 0xff));
}
