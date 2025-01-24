#include "io.h"

void print(char * string, int color);
void next_char();
void next_line();
void update_cursor_pos();

int term_x, term_y = 0;

void print(char * string, int color)
{
    char *video = (char*)0xb8000;

    while (*string != 0)
    {
        if (*string == '\n')
        {
            next_line();
            *string++;
        }
        else
        {
            *(video + (term_x * 2) + (term_y * 160)) = *string++;
            *(video + (term_x * 2) + (term_y * 160) + 1) = color;
            next_char();
        }
    }

    update_cursor_pos();
}

void next_char()
{
    term_x += 1;

    if (term_x >= 80)
    {
        next_line();
    }
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
