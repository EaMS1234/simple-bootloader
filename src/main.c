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
        print("Found ID ", 7);
        outb(0x60, 0xf2);
        print_int(inb(0x60), 7);
        print("\n", 7);
    }
}
