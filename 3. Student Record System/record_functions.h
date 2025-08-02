#ifndef RECORD_FUNCTIONS_H
#define RECORD_FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_RECORDS 100
#define NAME_LENGTH 50
#define ID_LENGTH 13
#define GRADE_LENGTH 6
#define ADDRESS_LENGTH 100

typedef struct
{
    char name[NAME_LENGTH];
    char id[ID_LENGTH];
    char grade[GRADE_LENGTH];
    char address[ADDRESS_LENGTH];
} StudentRecord;

void addStudentRecord(StudentRecord records[], int *count);
void deleteStudentRecord(int count, int record_no);
void updateStudentRecord(int count, int record_no);
void viewAllStudentRecords(const StudentRecord *records, int count);
int getRecordCount(int count);
// Function to clear the input buffer
void clearBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ; // Clear input buffer
}
// Function to get the count of student records from the file
int getRecordCount(int count)
{
    char line[256];
    FILE *fp = fopen("student_records.txt", "r");
    count = 0;
    if (fp == NULL)
        return 0;
    while (fgets(line, sizeof(line), fp) != NULL)
    {
        int record_no;
        if (sscanf(line, "Record no: %d", &record_no) == 1)
            count++;
    }
    fclose(fp);
    return count;
}

// Function to add a student record
void addStudentRecord(StudentRecord records[], int *count)
{
    int continue_adding = 1;
    int choice;
    FILE *fp = fopen("student_records.txt", "a"); // Open in append mode

    if (fp == NULL)
    {
        printf("Error opening file for writing.\n");
        exit(1);
    }

    while (continue_adding)
    {
        system("cls");
        printf("-------- Add Student Record --------\n");
        if (*count >= MAX_RECORDS)
        {
            printf("Maximum record limit reached.\n");
            break;
        }
        StudentRecord new_record;
        printf("Enter student name: ");
        fgets(new_record.name, NAME_LENGTH, stdin);
        new_record.name[strcspn(new_record.name, "\n")] = 0;
        printf("Enter student ID: ");
        fgets(new_record.id, ID_LENGTH, stdin);

        new_record.id[strcspn(new_record.id, "\n")] = 0;
        printf("Enter student grade: ");
        fgets(new_record.grade, GRADE_LENGTH, stdin);
        new_record.grade[strcspn(new_record.grade, "\n")] = 0;
        printf("Enter student address: ");
        fgets(new_record.address, ADDRESS_LENGTH, stdin);
        new_record.address[strcspn(new_record.address, "\n")] = 0;
        records[*count] = new_record;
        fprintf(fp, "----------------------------------\n");
        fprintf(fp, "Record no: %d\nName: %s\nID: %s\nGrade: %s\nAddress: %s\n", *count + 1, new_record.name, new_record.id, new_record.grade, new_record.address);
        printf("Record added successfully!\n");
        (*count)++;

        printf("Do you want to add another record? (1 for Yes, 0 for No): ");
        scanf("%d", &choice);
        clearBuffer();
        if (choice != 1)
        {
            continue_adding = 0;
            fclose(fp); // Close file after adding records
        }
    }
}

void deleteStudentRecord(int count, int record_no)
{
    system("cls");
    if (count == 0)
    {
        printf("No student records found.\n");
        return;
    }
    printf("\n----- Delete Student Record -----\n");

    FILE *fp = fopen("student_records.txt", "r");
    if (fp == NULL)
    {
        printf("Error opening file for reading.\n");
        exit(1);
    }

    FILE *temp_fp = fopen("temp_records.txt", "w");
    if (temp_fp == NULL)
    {
        printf("Error opening temporary file.\n");
        fclose(fp);
        exit(1);
    }

    char line[256];
    int current_record = 0;
    int skip = 0;
    int found = 0;

    while (fgets(line, sizeof(line), fp) != NULL)
    {
        if (strncmp(line, "Record no:", 10) == 0)
        {
            int rec_no;
            if (sscanf(line, "Record no: %d", &rec_no) == 1)
            {
                if (rec_no == record_no)
                {
                    skip = 1;
                    found = 1;
                }
                else
                {
                    skip = 0;
                }
            }
        }
        if (!skip)
        {
            int rec_no;
            if (sscanf(line, "Record no: %d", &rec_no) == 1)
            {
                if (rec_no > record_no)
                {
                    char temp[256];
                    sprintf(temp, "Record no: %d\n", rec_no - 1);
                    fputs(temp, temp_fp);
                }
                else
                {
                    fputs(line, temp_fp);
                }
            }
            else
            {
                fputs(line, temp_fp);
            }
        }
    }

    fclose(fp);
    fclose(temp_fp);

    if (found)
    {
        remove("student_records.txt");
        rename("temp_records.txt", "student_records.txt");
        printf("Record no %d deleted successfully.\n", record_no);
    }
    else
    {
        remove("temp_records.txt");
        printf("Record no %d not found.\n", record_no);
    }
}

void updateStudentRecord(int count, int record_no)
{
    system("cls");
    printf("-------- Update Student Record --------\n");

    FILE *fp = fopen("student_records.txt", "r");
    if (fp == NULL)
    {
        printf("Error opening file for reading.\n");
        exit(1);
    }

    FILE *temp_fp = fopen("temp_records.txt", "w");
    if (temp_fp == NULL)
    {
        printf("Error opening temporary file.\n");
        fclose(fp);
        exit(1);
    }

    char line[256];
    int current_record = 0;
    int found = 0;
    StudentRecord updated_record;
    int in_record = 0;

    while (fgets(line, sizeof(line), fp) != NULL)
    {
        if (strncmp(line, "Record no:", 10) == 0)
        {
            int rec_no;
            if (sscanf(line, "Record no: %d", &rec_no) == 1)
            {
                current_record = rec_no;
                if (rec_no == record_no)
                {
                    found = 1;
                    in_record = 1;
                    fprintf(temp_fp, "%s", line); // Write the record no line
                    // Prompt for new values
                    // Name
                    fgets(line, sizeof(line), fp); // Read Name line
                    sscanf(line, "Name: %[^\n]", updated_record.name);
                    clearBuffer();
                    printf("Current Name: %s\n", updated_record.name);
                    printf("Enter new name (or press Enter to keep current): ");
                    char input[NAME_LENGTH];
                    fgets(input, NAME_LENGTH, stdin);
                    if (input[0] != '\n')
                        input[strcspn(input, "\n")] = 0, strcpy(updated_record.name, input);
                    fprintf(temp_fp, "Name: %s\n", updated_record.name);

                    // ID
                    fgets(line, sizeof(line), fp); // Read ID line
                    sscanf(line, "ID: %[^\n]", updated_record.id);
                    printf("Current ID: %s\n", updated_record.id);
                    printf("Enter new ID (or press Enter to keep current): ");
                    fgets(input, ID_LENGTH, stdin);
                    if (input[0] != '\n')
                        input[strcspn(input, "\n")] = 0, strcpy(updated_record.id, input);
                    fprintf(temp_fp, "ID: %s\n", updated_record.id);

                    // Grade
                    fgets(line, sizeof(line), fp); // Read Grade line
                    sscanf(line, "Grade: %[^\n]", updated_record.grade);
                    printf("Current Grade: %s\n", updated_record.grade);
                    printf("Enter new grade (or press Enter to keep current): ");
                    fgets(input, GRADE_LENGTH, stdin);
                    if (input[0] != '\n')
                        input[strcspn(input, "\n")] = 0, strcpy(updated_record.grade, input);
                    fprintf(temp_fp, "Grade: %s\n", updated_record.grade);

                    // Address
                    fgets(line, sizeof(line), fp); // Read Address line
                    sscanf(line, "Address: %[^\n]", updated_record.address);
                    printf("Current Address: %s\n", updated_record.address);
                    printf("Enter new address (or press Enter to keep current): ");
                    fgets(input, ADDRESS_LENGTH, stdin);
                    if (input[0] != '\n')
                        input[strcspn(input, "\n")] = 0, strcpy(updated_record.address, input);
                    fprintf(temp_fp, "Address: %s\n", updated_record.address);
                    in_record = 0;
                }
                else
                {
                    in_record = 1;
                    fprintf(temp_fp, "%s", line);
                }
            }
        }
        else if (in_record)
        {
            fprintf(temp_fp, "%s", line);
        }
        else if (strncmp(line, "----------------------------------", 34) == 0)
        {
            fprintf(temp_fp, "%s", line);
        }
    }

    fclose(fp);
    fclose(temp_fp);

    if (found)
    {
        remove("student_records.txt");
        rename("temp_records.txt", "student_records.txt");
        printf("Record no %d updated successfully.\n", record_no);
    }
    else
    {
        remove("temp_records.txt");
        printf("Record no %d not found.\n", record_no);
    }
}

void viewAllStudentRecords(const StudentRecord *records, int count)
{
    FILE *fp = fopen("student_records.txt", "r");
    system("cls");
    if (fp == NULL)
    {
        printf("Error opening file for reading.\n");
        exit(1);
    }
    printf("----- All Student Records -----\n");
    if (count == 0)
    {
        printf("No student records found.\n");
    }
    else
    {
        char line[256];
        while (fgets(line, sizeof(line), fp) != NULL)
        {
            printf("%s", line);
        }
        fclose(fp);
    }
}

#endif