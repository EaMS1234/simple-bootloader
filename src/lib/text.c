void print(char * string, int color);
void next_char();
void next_line();

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
}
