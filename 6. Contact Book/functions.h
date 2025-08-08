#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graphics.h"

struct contact
{
    char name[100];
    char phone[15];
};
typedef struct contact Contact;
struct node
{
    Contact contact;
    struct node *next;
};
typedef struct node node_c;

node_c *applyFileChange(node_c *head)
{
    node_c *temp = head;
    FILE *file = fopen("contacts.txt", "w");
    while (temp != NULL)
    {
        fprintf(file, "%s %s\n", temp->contact.name, temp->contact.phone);
        temp = temp->next;
    }
    fclose(file);
}
node_c *createNode(Contact con)
{
    node_c *result = (node_c *)malloc(sizeof(node_c));
    result->contact = con;
    result->next = NULL;
    return result;
}
node_c *printAllNodes(node_c *head, char header[], char footer[])
{
    int running = 1;
    int active = 0;
    node_c *selectedOption = NULL;

    while (running)
    {
        node_c *temp = head;
        int count = 0;
        system("cls");
        printf("\033[?25l");
        if (header[0] != '\0')
        {
            printf("------- %s -------\n", header);
        }
        while (temp != NULL)
        {
            if (count == active)
            {
                printHighlightedString(temp->contact.name);
                selectedOption = temp;
            }
            else
            {
                printf("%s\n", temp->contact.name);
            }
            temp = temp->next;
            count++;
        }
        if (count == 0)
        {
            printf("No contact found\n");
            return NULL;
        }
        if (footer[0] != '\0')
        {
            printf("%s\n", footer);
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
            running = 0;
            return selectedOption;
        }
        // system("cls"); // Already cleared at the top of the loop
    }
    return -1;
}
node_c *searchContactNode(node_c *head, char name[50])
{
    node_c *temp = head;
    while (temp != NULL)
    {
        if (strcmp(temp->contact.name, name) == 0)
        {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}
node_c *getStartnode()
{
    FILE *file = fopen("contacts.txt", "r");
    if (file == NULL)
    {
        perror("Unable to open file");
        return NULL;
    }
    node_c *head = NULL, *temp = NULL;
    Contact current;
    char line[256];
    while (fgets(line, sizeof(line), file))
    {
        sscanf(line, "%s %s", current.name, current.phone);
        temp = createNode(current);

        if (head == NULL)
        {
            head = temp;
        }
        else
        {
            temp->next = head;
            head = temp;
        }
    }
    fclose(file);
    return head;
}
node_c *deleteNode(node_c *head, char name[50])
{
    node_c *prev = NULL;
    node_c *temp = head;
    while (temp != NULL)
    {
        if (strcmp(temp->contact.name, name) == 0)
        {
            if (prev == NULL)
            {
                prev = temp->next;
                free(temp);
                applyFileChange(prev);
                return prev;
            }
            prev->next = temp->next;
            free(temp);
        }
        prev = temp;
        temp = temp->next;
    }
    applyFileChange(head);
    return head;
}
node_c *updateNode(node_c *head, char name[50], char newName[50], char newPhone[50])
{
    node_c *temp = head;
    while (temp != NULL)
    {
        if (strcmp(temp->contact.name, name) == 0)
        {
            strcpy(temp->contact.name, newName);
            strcpy(temp->contact.phone, newPhone);
            applyFileChange(head);
            return head;
        }
        temp = temp->next;
    }
}

void viewContacts()
{
    FILE *file = fopen("contacts.txt", "r");
    if (file == NULL)
    {
        perror("Unable to open file");
        return;
    }
    char line[256];
    system("cls");
    printf("\033[?25h");
    printf("Contacts:\n");
    int count = 1;
    while (fgets(line, sizeof(line), file))
    {
        // Remove newline character if present
        line[strcspn(line, " ")] = '\t'; // Replace the first space with a newline
        printf("%d. %s", count, line);
        count++;
    }
    fclose(file);
    printf("\nPress any key to continue...");
    getch();
    system("cls");
    printf("\033[?25l");
}

void addContact()
{
    FILE *file = fopen("contacts.txt", "a");
    if (file == NULL)
    {
        perror("Unable to open file");
        return;
    }
    int condition = 1;
    while (condition)
    {
        char name[100];
        char phone[15];
        system("cls");
        printf("\033[?25h");
        printf("Enter name: ");
        fgets(name, sizeof(name), stdin);
        name[strcspn(name, "\n")] = 0; // Remove newline character
        printf("Enter phone number: ");
        fgets(phone, sizeof(phone), stdin);
        phone[strcspn(phone, "\n")] = 0; // Remove newline character
        fprintf(file, "%s %s\n", name, phone);
        system("cls");
        printf("\033[?25l");
        int choice = displayOptions((char *[]){"Yes", "No"}, "Add Contact", "Do you want to add another contact", 2, 0);
        if (choice == 0)
        {
            condition = 1; // Continue adding contacts
        }
        else
        {
            condition = 0; // Stop adding contacts
        }
    }
    fclose(file);
}

void deleteContact()
{
    int running = 1;
    node_c *head = getStartnode();
    char header[] = "Delete Contact";
    while (running)
    {
        int choice;
        node_c *result = printAllNodes(head, header, "Select the one to be deleted");
        if (result != NULL)
        {
            head = deleteNode(head, result->contact.name);
            printf("\033[?25l");
            choice = displayOptions((char *[]){"Yes", "No"}, "Delete Contact", "Do you want to Delete another contact", 2, 0);
        }
        else
        {
            printf("\033[?25l");
            printf("Press Enter to go back\n");
            getch();
            choice = 1;
        }
        if (choice == 0)
        {
            running = 1; // Continue adding contacts
        }
        else
        {
            running = 0; // Stop adding contacts
        }
    }
}

void searchContact()
{
    system("cls");
    printf("------- Search Contact -------\n");
    char name[50];
    printf("\033[?25h");
    printf("Enter the name you want to search: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = 0;
    printf("\033[?25l");
    node_c *head, *result;
    head = getStartnode();
    result = searchContactNode(head, name);
    if (result != NULL)
    {
        printf("The number of the contact is: %s", result->contact.phone);
        getch();
        return;
    }
    printf("No contact of such name was found\n");
    getch();
}

void updateContact()
{
    node_c *head = getStartnode();
    int running = 1;
    while (running)
    {
        char header[] = "Update Contact";
        node_c *result = printAllNodes(head, header, "Choose the option to be updated");
        if (result != NULL)
        {
            char newName[100];
            char newPhone[15];
            system("cls");
            printf("\033[?25h");
            printf("Enter new name: ");
            fgets(newName, sizeof(newName), stdin);
            newName[strcspn(newName, "\n")] = 0; // Remove newline character
            printf("Enter new phone number: ");
            fgets(newPhone, sizeof(newPhone), stdin);
            newPhone[strcspn(newPhone, "\n")] = 0; // Remove newline character
            head = updateNode(head, result->contact.name, newName, newPhone);
            printf("\033[?25l");
            int choice = displayOptions((char *[]){"Yes", "No"}, "Update Contact", "Do you want to update another contact", 2, 0);
            if (choice == 0)
            {
                running = 1; // Continue updating contacts
            }
            else
            {
                running = 0; // Stop updating contacts
            }
        }
        else
        {
            printf("\033[?25l");
            printf("Press Enter to go back\n");
            getch();
            running = 0;
        }
    }
}
#endif