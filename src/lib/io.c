#include <stdint.h>

// Output byte to port
void outb(uint16_t port, uint8_t value)
{
    // Voltaile ensures it won't be optimized by the compiler
    asm volatile ("outb %b0, %w1" // Byte 0, word 1
        :                         // Output (empty)
        : "a"(value), "Nd"(port)  // Input. Ensure (value) is at EAX (accumulator)
                                  // and (port) is at EDX (Data).
        : "memory");              // Works in conjunction with volatile to
                                  // problems with the asm code and compiler.
}

// Input byte from port
uint8_t inb(uint16_t port)
{
    uint8_t value;

    asm volatile ("inb %w1, %b0" // Word 0, byte 1
        : "=a"(value)            // Output (EAX to value)
        : "Nd"(port)             // Input (port to EDX)
        : "memory");
}
