#include <stdio.h>
#include <stdbool.h>
#include "math_functions.h"

int main() {
    bool running = true;

    while(running){
        int choice, a, b, result;
        
        
        printf("***** Calculator *****\n");

        printf("1. Add\n");
        printf("2. Subtract\n");
        printf("3. Multiply\n");
        printf("4. Divide\n");
        printf("5. Modulus\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 6) {
            running = false;
            continue;
        }
        if (choice < 1 || choice > 6) {
            printf("Invalid choice. Please try again.\n");
            printf("Leaving program....\n");
            running = false;
            continue;
        }
        printf("Enter two integers: ");
        scanf("%d %d", &a, &b);


        
        switch(choice) {
            case 1:
                result = add(a, b);
                printf("Result: %d + %d = %d\n", a, b, result);
                break;
            case 2:
                result = subtract(a, b);
                printf("Result: %d - %d = %d\n", a, b, result);
                break;
            case 3:
                result = multiply(a, b);
                printf("Result: %d * %d = %d\n", a, b, result);
                break;
            case 4:
                result = divide(a, b);
                if (b == 0) {
                    printf("Error: Division by zero is not allowed.\n");
                } else {
                    printf("Result: %d / %d = %d\n", a, b, result);
                }
                break;
            case 5:
                result = modulus(a, b);
                if (b == 0) {
                    printf("Error: Modulus by zero is not allowed.\n");
                } else {
                    printf("Result: %d %% %d = %d\n", a, b, result);
                }
                break;
            default:
                printf("Leaving program....\n");
                continue;
        }
        
        printf("\n");

    }
    
    return 0;
}