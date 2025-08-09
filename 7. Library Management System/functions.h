#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include "graphics.h"
#include "definitions.h"
Book *createBook(Details detail);
Book *getStartPoint(void);
Book *getAvailableBooks(Book *head);
Book *getBorrowedBooks(Book *head, String borrowerName);
void freeBooks(Book *head);
void viewBooks(void);
void borrowBook(void);
void returnBook(void);

void writeBookChangesToFile(Book *head, Book *borrowedHead)
{
    FILE *file = fopen("temp.txt", "w");
    // FILE *file = fopen("Books.txt", "a+");
    if (file == NULL)
    {
        perror("Unable to open file for writing");
        return;
    }
    Book *temp = head;
    Book *borrowedTemp = borrowedHead;
    while (temp != NULL)
    {
        if (strcmp(temp->detail.name, borrowedTemp->detail.name) == 0)
        {
            fprintf(file, "%s-%s-%s\n", borrowedTemp->detail.name, borrowedTemp->detail.availability, borrowedTemp->detail.borrower);
        }
        else
        {
            fprintf(file, "%s-%s-%s\n", temp->detail.name, temp->detail.availability, temp->detail.borrower);
        }

        temp = temp->next;
    }
    fclose(file);
    remove("Books.txt");
    rename("temp.txt", "Books.txt");
}

Book *createBook(Details detail)
{
    Book *head = (Book *)malloc(sizeof(Book));
    head->detail = detail;
    head->next = NULL;
    return head;
}
Book *getStartPoint()
{
    FILE *file = fopen("Books.txt", "r");
    char line[256];
    Book *head = NULL;
    Book *tail = NULL;

    if (file == NULL)
    {
        perror("Unable to open file");
        return NULL;
    }
    while (fgets(line, sizeof(line), file))
    {
        Details bdeta;
        char name[100], availability[100], borrower[100];
        if (sscanf(line, "%99[^-]-%99[^-]-%99[^\n]", name, availability, borrower) == 3)
        {
            bdeta.name = malloc(strlen(name) + 1);
            bdeta.availability = malloc(strlen(availability) + 1);
            bdeta.borrower = malloc(strlen(borrower) + 1);
            if (!bdeta.name || !bdeta.availability || !bdeta.borrower)
            {
                // handle allocation failure
                continue;
            }
            strcpy(bdeta.name, name);
            strcpy(bdeta.availability, availability);
            strcpy(bdeta.borrower, borrower);

            Book *newBook = createBook(bdeta);
            if (head == NULL)
            {
                head = newBook;
                tail = newBook;
            }
            else
            {
                tail->next = newBook;
                tail = newBook;
            }
        }
    }
    fclose(file);
    return head;
}
Book *getAvailableBooks(Book *head)
{
    Book *curr = head;
    Book *prev = NULL;
    while (curr != NULL)
    {
        if (strcmp(curr->detail.availability, "Available") != 0)
        {
            Book *toDelete = curr;
            if (prev == NULL)
            {
                head = curr->next;
                curr = head;
            }
            else
            {
                prev->next = curr->next;
                curr = curr->next;
            }
            free(toDelete->detail.name);
            free(toDelete->detail.availability);
            free(toDelete->detail.borrower);
            free(toDelete);
        }
        else
        {
            prev = curr;
            curr = curr->next;
        }
    }
    return head;
}
Book *getBorrowedBooks(Book *head, String borrowerName)
{
    Book *curr = head;
    Book *prev = NULL;
    while (curr != NULL)
    {
        if (strcmp(curr->detail.availability, "Available") == 0, strcmp(curr->detail.borrower, borrowerName) != 0)
        {
            Book *toDelete = curr;
            if (prev == NULL)
            {
                head = curr->next;
                curr = head;
            }
            else
            {
                prev->next = curr->next;
                curr = curr->next;
            }
            free(toDelete->detail.name);
            free(toDelete->detail.availability);
            free(toDelete->detail.borrower);
            free(toDelete);
        }
        else
        {
            prev = curr;
            curr = curr->next;
        }
    }
    return head;
}
void freeBooks(Book *head)
{
    Book *temp;
    while (head != NULL)
    {
        temp = head;
        head = head->next;
        free(temp);
    }
}

void viewBooks()
{
    Book *head = getStartPoint();
    String header = "ALL BOOKS";
    String footer = "Press enter to go back";
    displayBookGraphics(header, footer, head);
    freeBooks(head);
}
void borrowBook()
{
    Book *head = getStartPoint();
    head = getAvailableBooks(head);
    String header = "BORROW BOOKS";

    String footer = "Select the book you want to borrow";
    printf("Please enter your name: ");
    char borrowerName[100];
    fgets(borrowerName, sizeof(borrowerName), stdin);
    borrowerName[strcspn(borrowerName, "\n")] = 0; // Remove newline character
    Option options = displayBookGraphics(header, footer, head);
    freeBooks(head);
    head = getStartPoint();
    options.choice->detail.borrower = malloc(strlen(borrowerName) + 1);
    strcpy(options.choice->detail.borrower, borrowerName);
    printf("You have borrowed the book: %s\n", options.choice->detail.name);
    options.choice->detail.availability = "Not Available";
    writeBookChangesToFile(head, options.choice);
    freeBooks(head);
    printf("Press enter to go back to the main menu.");
    getchar(); // Wait for user input before returning to main menu
    system("cls");
}
void returnBook()
{
    Book *head = getStartPoint();
    String header = "RETURN BOOKS";

    String footer = "Select the book you want to return";
    printf("Please enter your name: ");
    char borrowerName[100];
    fgets(borrowerName, sizeof(borrowerName), stdin);
    borrowerName[strcspn(borrowerName, "\n")] = 0; // Remove newline character
    head = getBorrowedBooks(head, borrowerName);
    Option options = displayBookGraphics(header, footer, head);
    freeBooks(head);
    head = getStartPoint();
    options.choice->detail.borrower = malloc(strlen(borrowerName) + 1);
    strcpy(options.choice->detail.borrower, "none");
    printf("You have borrowed the book: %s\n", options.choice->detail.name);
    options.choice->detail.availability = "Available";
    writeBookChangesToFile(head, options.choice);
    freeBooks(head);
    printf("Press enter to go back to the main menu.");
    getchar(); // Wait for user input before returning to main menu
    system("cls");
}
#endif