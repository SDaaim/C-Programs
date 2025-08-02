#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

int main()
{

    int running = 1;
    int taskCount = 0; // Initialize task count
    while (running)
    {
        int choice;
        taskCount = getTaskCount(); // Get the initial task count
        clearScreen();              // Clear the screen before displaying the menu
        printf("------ ToDo List ------\n");
        printf("CURRENT TASK COUNT: %d\n", taskCount);
        printf("1. Add Task\n");
        printf("2. View Tasks\n");
        printf("3. Remove Task\n");
        printf("4. Completed Task\n");
        printf("5. Exit\n");
        printf("-----------------------\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        clearBuffer(); // Clear the input buffer after reading choice
        switch (choice)
        {
        case 1:
            addTask(taskCount); // Call the function to add a task
            break;
        case 2:
            viewTasks(taskCount); // Call the function to view tasks
            break;
        case 3:
            removeTask(taskCount); // Call the function to remove a task
            break;
        case 4:
            markTaskCompleted(taskCount); // Call the function to mark a task as completed
            // Code to mark a task as completed would go here
            break;
        case 5:
            running = 0; // Exit the loop
            printf("Exiting the ToDo List.\n");
            break;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    }
}