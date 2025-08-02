#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int checkGuess(int guess, int number)
{
    if (guess > number)
    {
        return 1;
    }
    else if (guess < number)
    {
        return -1;
    }
    else if (guess = number)
    {
        return 0;
    }
}

int main()
{
    srand(time(NULL));
    int number, guess, attempts;
    int running = 1;
    number = (rand() % 100) + 1;
    printf("------ NUMBER GUESSING GAME ------\n");
    printf("# Instructions:\n");
    printf("1. Guess a number between 1 and 100.\n");
    printf("2. If the number is higher then the answer, you will get a message \"TOO HIGH\"\n");
    printf("3. If the number is lower then the answer, you will get a message \"TOO LOW\"\n");
    printf("4. You get 10 attempts to guess the number, after which the game will be over.\n");
    printf("\n\n");

    while (running)
    {
        printf("Attempts left: %d\n", 10 - attempts);
        printf("Guess the number: ");
        scanf("%d", &guess);
        system("cls");
        if (checkGuess(guess, number) == 0)
        {
            system("cls");
            printf("The answer was: %d\n", number);
            printf("Congratulations, You won !\n");
            running = 0;
            break;
        }
        else if (checkGuess(guess, number) == 1)
        {
            printf("TOO HIGH\n");
            attempts++;
        }
        else if (checkGuess(guess, number) == -1)
        {
            printf("TOO LOW\n");
            attempts++;
        }
        if (attempts == 10)
        {
            system("cls");
            printf("The answer was: %d\n", number);
            printf("You are out of attempts, Try again\n");
            running = 0;
        }
    }
    printf("------ THANKS FOR PLAYING ------");
}