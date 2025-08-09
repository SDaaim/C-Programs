#include <stdio.h>
#include <stdlib.h>
#include "graphics.h"
#include "functions.h"
#include "definitions.h"

int main()
{
    String header = "LIBRARY MANAGEMENT SYSTEM";
    String footer = "Select from the given options";
    String options[] = {
        "View All Books", "Borrow Book", "Return Book", "Exit"};
    int condition = 1;
    while (condition)
    {
        int result = displayGraphics(header, footer, options, 4);

        switch (result)
        {
        case 0:
            viewBooks();
            break;
        case 1:
            borrowBook();
            break;
        case 2:
            returnBook();
            break;
        default:
            condition = 0;
            break;
        }
    }

    return 0;
}