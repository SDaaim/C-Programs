#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void clearScreen()
{
    system("cls"); // Clear the console screen
}
void clearBuffer()
{
    while (getchar() != '\n')
        ; // Clear the input buffer
}
int getTaskCount()
{
    FILE *file = fopen("tasks.txt", "r");
    if (file == NULL)
    {
        return 0; // If file doesn't exist, return 0
    }

    int count = 0;
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file) != NULL)
    {
        count++;
    }
    fclose(file);
    return count;
}

void addTask(int count);
void viewTasks(int count);
void removeTask(int count);
void markTaskCompleted(int count); // Function prototype for marking a task as completed

// Function to add a task
void addTask(int count)
{
    int running = 1;
    int taskCount = count; // Use the count passed from main
    do
    {
        char choice;
        clearScreen();
        printf("------ Add Task ------\n");

        // Creating a file
        FILE *file = fopen("tasks.txt", "a");
        if (file == NULL)
        {
            printf("Error opening file!\n");
            return;
        }

        // Get task title from user
        char task[100];
        printf("Enter the task Title: ");
        fgets(task, sizeof(task), stdin);

        // Remove newline character from the end of the string
        task[strcspn(task, "\n")] = 0;

        // Write task to file
        fprintf(file, "%s - pending\n", task);
        fclose(file);
        printf("Do you want to add another task?: (y/n) ");
        taskCount++;
        scanf(" %c", &choice);
        clearBuffer();
        if (choice == 'n' || choice == 'N')
        {
            running = 0; // Exit the loop
            printf("Returning to main menu...\n");
        }
        else if (choice != 'y' && choice != 'Y')
        {
            printf("Invalid choice. Returning to main menu...\n");
            running = 0; // Exit the loop
        }

    } while (running);
}
// Funtion to view tasks
void viewTasks(int count)
{
    clearScreen();

    printf("------ View Tasks ------\n");
    FILE *file = fopen("tasks.txt", "r");
    if (file == NULL)
    {
        printf("No tasks found.\n");
        return;
    }

    int taskCount = 1;
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file) != NULL)
    {
        printf("%d. %s", taskCount++, buffer);
    }
    fclose(file);
    printf("Press Enter to return to the main menu...");
    getchar(); // Wait for user input
}
// Function to remove a task
void removeTask(int count)
{
    clearScreen();
    if (count == 0)
    {
        printf("No tasks to remove.\n");
        printf("Press Enter to return to the main menu...");
        getchar(); // Wait for user input
        return;
    }
    printf("------ Remove Task ------\n");
    FILE *file = fopen("tasks.txt", "r");
    if (file == NULL)
    {
        printf("No tasks found.\n");
        return;
    }

    // Read all tasks into an array

    char tasks[100][256];
    int taskCount = 0;
    while (fgets(tasks[taskCount], sizeof(tasks[taskCount]), file) != NULL)
    {
        taskCount++;
    }
    fclose(file);

    // Display tasks
    for (int i = 0; i < taskCount; i++)
    {
        printf("%d: %s", i + 1, tasks[i]);
    }

    // Get task number to remove
    int taskNumber;
    printf("Enter the task number to remove: ");
    scanf("%d", &taskNumber);
    clearBuffer();

    if (taskNumber < 1 || taskNumber > taskCount)
    {
        printf("Invalid task number.\n");
        return;
    }

    // Write remaining tasks back to file
    file = fopen("tasks.txt", "w");
    if (file == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    for (int i = 0; i < taskCount; i++)
    {
        if (i != taskNumber - 1) // Skip the task to remove
        {
            fprintf(file, "%s", tasks[i]);
        }
    }

    fclose(file);

    printf("Task %d removed successfully.\n", taskNumber);
}
// Function to mark a task as completed
void markTaskCompleted(int count)
{
    clearScreen();
    if (count == 0)
    {
        printf("No tasks to mark as completed.\n");
        printf("Press Enter to return to the main menu...");
        getchar(); // Wait for user input
        return;
    }
    printf("------ Mark Task Completed ------\n");
    FILE *file = fopen("tasks.txt", "r");
    if (file == NULL)
    {
        printf("No tasks found.\n");
        return;
    }

    // Read all tasks into an array
    char tasks[100][256];
    int taskCount = 0;
    while (fgets(tasks[taskCount], sizeof(tasks[taskCount]), file) != NULL)
    {
        taskCount++;
    }
    fclose(file);

    // Display tasks
    for (int i = 0; i < taskCount; i++)
    {
        printf("%d: %s", i + 1, tasks[i]);
    }

    // Get task number to mark as completed
    int taskNumber;
    printf("Enter the task number to mark as completed: ");
    scanf("%d", &taskNumber);
    clearBuffer();

    if (taskNumber < 1 || taskNumber > taskCount)
    {
        printf("Invalid task number.\n");
        return;
    }

    // Write updated tasks back to file
    FILE *tempFile = fopen("temp.txt", "w");

    if (tempFile == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    for (int i = 0; i < taskCount; i++)
    {
        if (i == taskNumber - 1) // Mark this task as completed
        {
            // Remove trailing newline
            char *newline = strchr(tasks[i], '\n');
            if (newline)
                *newline = '\0';

            // Find last occurrence of " - " to replace status
            char *status = strrchr(tasks[i], '-');
            if (status && status > tasks[i] && *(status - 1) == ' ')
            {
                *(status - 1) = '\0'; // Remove space before '-'
            }
            fprintf(tempFile, "%s - completed\n", tasks[i]);
        }
        else
        {
            fprintf(tempFile, "%s", tasks[i]);
        }
    }
    fclose(tempFile);
    remove("tasks.txt");             // Remove the old file
    rename("temp.txt", "tasks.txt"); // Replace the old file with the new one

    printf("Task %d marked as completed successfully.\n", taskNumber);
}

#endif