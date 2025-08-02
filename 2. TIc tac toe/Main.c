#include <stdio.h>
#include <stdlib.h>
#include "game.h"

int main()
{
    int running = 1;
    int choice;
    do
    {
        printf("----- Welcome to Tic Tac Toe -----\n");
        printf("Please choose:\n 1.Play Game Again\n 2.Exit\n");
        scanf("%d", &choice);
        if (choice == 1)
        {
            run_game();
        }
        else
        {
            printf("----- Thanks for playing -----\n");
            return 0;
        }

    } while (running);

    return 0;
}