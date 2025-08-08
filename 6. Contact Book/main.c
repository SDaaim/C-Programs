#include <stdio.h>
#include <stdlib.h>
#include "graphics.h"
#include "functions.h"

int main()
{
    int running = 1;
    char *options[] = {
        "View all contacts", "Add contact", "Delete contact", "Search contact", "Update contact", "EXIT"};
    char footer[] = "Press the arrow up / arrow down key to select the option and press enter to submit:";
    while (running)
    {
        int choice = 0;
        system("cls");
        choice = displayOptions(options, "CONTACT BOOK", footer, 6, choice);

        switch (choice)
        {
        case 0:
            viewContacts();
            break;
        case 1:
            addContact();
            break;
        case 2:
            deleteContact();
            break;
        case 3:
            searchContact();
            break;
        case 4:
            updateContact();
            break;
        case 5:
            printf("EXITING PROGRAM....");
            running = 0;
            break;

        default:
            break;
        }
    }
    return 0;
}