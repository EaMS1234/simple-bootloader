#include "lib/text.h"

extern void main()
{
    print("Welcome to ", 7);
    print("Simple-Bootloader", 3);
    print("!\n\n", 7);

    for (int i = 0; i <= 16; i++)
    {
        print_int(i, i);
    }

    print("\n", 7);
    print_int(-827, 7);
}
