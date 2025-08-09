#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char *String;

typedef struct Details
{
    String name;
    String availability;
    String borrower;
} Details;

typedef struct Book
{
    Details detail;
    struct Book *next;
} Book;

typedef struct Option
{
    int active;
    Book *choice;
} Option;

#endif