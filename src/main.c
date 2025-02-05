#include "lib/text.h"
#include "lib/io.h"

extern void main()
{
    print("Welcome to ", 7);
    print("Simple-Bootloader", 3);
    print("!\n\n", 7);

    print("Looking for keyboard on 0x60... ", 7);

    outb(0x60, 0xee);
    if (inb(0x60) != 0xee)
    {
        print("Failed!\n", 7);
    }
    else
    {
        print("Found ", 7);
        outb(0x60, 0xf2);

        // Responds with 0xfa + keyboard id
        inb(0x60);
        print_hex(inb(0x60), 7);
        print(" (ID ", 7);
        print_hex(inb(0x60), 7);
        print(") ", 7);

        // Gets current scan code
        outb(0x60, 0xf0);
        outb(0x60, 0);
        
        // Displays current scancode if keyboard acknowledged the command
        if (inb(0x60) != 0xfe)
        {
            print("(Scan code ", 7);
            print_hex(inb(0x60), 7);
            print(")", 7);
        }

        print("\n", 7);
    }
}
