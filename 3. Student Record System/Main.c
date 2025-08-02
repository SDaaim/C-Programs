#include <stdio.h>
#include <stdlib.h>
#include "record_functions.h"

int main()
{
    int running = 1;

    system("cls");
    int count = 0;

    count = getRecordCount(count);
    printf("Total records found: %d\n", count);

    StudentRecord records[MAX_RECORDS];

    do
    {
        int choice;
        printf("------ STUDENT RECORD SYSTEM -------\n");
        printf("Choose from the following options: \n");
        printf("1. Add student record\n2. Deleted student record\n3. Update student record\n4. View all student records\n");
        printf("5. Exit\n");
        printf("Choose between 1 - 5 : ");

        scanf("%d", &choice);
        clearBuffer();

        switch (choice)
        {
        case 1:
        {
            addStudentRecord(records, &count);
            viewAllStudentRecords(records, count);
        }
        break;

        case 2:
        {
            int record_no;
            viewAllStudentRecords(records, count);
            printf("Enter record no to delete: ");
            scanf("%d", &record_no);
            clearBuffer();
            deleteStudentRecord(count, record_no);
        }
        break;

        case 3:
        {
            int record_no;
            viewAllStudentRecords(records, count);
            printf("Enter record no to update: ");
            scanf("%d", &record_no);
            updateStudentRecord(count, record_no);
        }

        break;

        case 4:
        {
            viewAllStudentRecords(records, count);
            printf("Press any key to continue...");
            getchar(); // Wait for user input
        }
        break;

        case 5:
            system("cls");
            printf("EXITING THE PROGRAM...");
            return 0;

        default:
            system("cls");
            printf("WRONG OPTION\nEXITING THE PROGRAM...");
            return 0;
            break;
        }
    } while (running);

    return 0;
}