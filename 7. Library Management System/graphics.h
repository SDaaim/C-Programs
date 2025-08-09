#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include "definitions.h"

Option displayBookGraphics(String header, String footer, Book *head);
void displayHeader(String header);
void displayFooter(String footer);
int displayGraphics(String header, String footer, String options[], int totalOptions);
void gotoxy(int x, int y);

// Displays a header
void gotoxy(int x, int y)
{
    COORD coord = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void displayHeader(String header)
{
    printf("-------- %s --------\n", header);
    return;
}
// Displays a footer
void displayFooter(String footer)
{
    printf("%s\n", footer);
}
// Display options that can be selected
int displayGraphics(String header, String footer, String options[], int totalOptions)
{
    int condition = 1;
    int active = 0;
    printf("\033[?25l");
    system("cls");
    while (condition)
    {
        gotoxy(0, 0);

        if (header != NULL)
        {
            displayHeader(header);
        }
        for (size_t i = 0; i < totalOptions; i++)
        {
            if (i == active)
            {

                printf("\033[1;31;41m%s\033[0m\n", options[i]);
            }
            else
            {
                printf("%s\n", options[i]);
            }
        }
        char ch = getch();
        if (ch == 72 && active > 0)
        {
            active--;
        }
        else if (ch == 80 && active < totalOptions - 1)
        {
            active++;
        }
        else if (ch == 13)
        {
            return active;
        }
    }
}

Option displayBookGraphics(String header, String footer, Book *head)
{
    int condition = 1;
    int active = 0;
    Book *choice = NULL;
    Option options;
    Book *temp = head;
    printf("\033[?25l");
    system("cls");
    while (condition)
    {
        gotoxy(0, 0);
        int count = 0;

        if (header != NULL)
        {
            displayHeader(header);
        }
        temp = head;
        count = 0;
        while (temp != NULL)
        {
            if (count == active)
            {
                printf("\033[1;31;41mBook name: %s\n%s\nBorrowed by: %s\033[0m\n\n", temp->detail.name, temp->detail.availability, temp->detail.borrower);

                choice = temp;
            }
            else
            {
                printf("Book name: %s\n%s\nBorrowed by: %s\n\n", temp->detail.name, temp->detail.availability, temp->detail.borrower);
            }
            temp = temp->next;
            count++;
        }
        char ch = getch();
        if (ch == 72 && active > 0)
        {
            active--;
        }
        else if (ch == 80 && active < count - 1)
        {
            active++;
        }
        else if (ch == 13)
        {
            options.active = 1;
            options.choice = choice;
            return options;
        }
    }
}
#endif