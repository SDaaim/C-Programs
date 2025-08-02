#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <stdlib.h>

char check_board(char board[3][3])
{
    for (size_t i = 0; i < 3; i++)
    {
        if (
            board[i][0] == board[i][1] && board[i][1] == board[i][2])
        {
            return board[i][0];
        }
        else if (board[0][i] == board[1][i] && board[1][i] == board[2][i])
        {
            return board[0][i];
        }
    }
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2])
    {
        return board[0][0];
    }
    else if (board[0][2] == board[1][1] && board[1][1] == board[2][0])
    {
        return board[0][2];
    }
    return 'N';
}

void render_board(char board[3][3])
{
    printf("_____________\n\n");
    for (size_t i = 0; i < 3; i++)
    {
        printf("| %c | %c | %c |\n", board[i][0], board[i][1], board[i][2]);
        printf("_____________\n\n");
    }
}

void run_game()
{
    int validMove = 1;
    char board[3][3] = {{'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'}};
    int choice;
    int player = 1;
    char mark = 'X';
    int turns = 0;
    int row, col;
    while (validMove)
    {
        system("cls");
        printf("***** BOARD GAME *****\n");
        render_board(board);
        printf("Player %d's turn to choose a number between 1 - 9: ", player);
        scanf("%d", &choice);
        col = (choice - 1) % 3;
        row = (choice - 1) / 3;
        if (choice < 1 || choice > 9 || board[row][col] == 'X' || board[row][col] == 'O')
        {
            printf("Invalid move! Ending Game....\n");
            validMove = 0;
        }
        else
        {
            board[row][col] = mark;

            if (check_board(board) == 'X')
            {
                printf("Player 1 won\n");
                printf("Ending game...\n");
                break;
            }
            else if (check_board(board) == 'O')
            {
                printf("Player 2 won\n");
                printf("Ending game...\n");
                break;
            }

            if (player == 1)
            {
                player++;
                mark = 'O';
            }
            else
            {
                player--;
                mark = 'X';
            }
        }
    }
}

#endif