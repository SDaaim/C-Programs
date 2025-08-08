#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#ifndef GRAPHICS_H
#define GRAPHICS_H

void printHighlightedString(char str[])
{
    printf("\033[1;4;47;34m%s\033[0m\n", str);
    return;
}

int displayOptions(char *str[], char header[], char footer[], int numOptions, int choice)
{
    int active = choice;
    int rendering = 1;
    system("cls");
    while (rendering)
    {
        printf("\033[?25l");
        if (header != "")
        {
            printf("------- %s -------\n", header);
        }
        for (size_t i = 0; i < numOptions; i++)
        {
            if (i == active)
            {
                printHighlightedString(str[i]);
            }
            else
            {
                printf("%s\n", str[i]);
            }
        }
        if (footer != "")
        {
            printf("%s\n", footer);
        }

        char ch = getch();
        if (ch == 72 && active > 0)
        {
            active--;
        }
        else if (ch == 80 && active < numOptions - 1)
        {
            active++;
        }
        else if (ch == 13)
        {
            return active;
        }
        system("cls");
    }
    return active;
}

#endif