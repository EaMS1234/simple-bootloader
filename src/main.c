void print(char * string, int color);
void next_char();
void next_line();

int term_x, term_y = 0;

extern void main()
{
    print("Welcome to ", 7);
    print("Simple-Bootloader", 3);
    print("!\n", 7);
    next_line();
}

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
}

void next_char()
{
    term_x += 1;
}

void next_line()
{
    term_x = 0;
    term_y += 1;    
}
