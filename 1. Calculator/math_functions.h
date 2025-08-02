#ifndef MATH_FUNCTIONS_H
#define MATH_FUNCTIONS_H

int add(int a, int b);
int subtract(int a, int b);
int multiply(int a, int b);
int divide(int a, int b);
int modulus(int a, int b);


int add(int a, int b) {
    return a + b;
}

int subtract(int a, int b) {
    return a - b;
}
int multiply(int a, int b) {
    return a * b;
}
int divide(int a, int b) {
    if (b == 0) {
        // Handle division by zero error
        return 0; // or some error code
    }
    return a / b;
}
int modulus(int a, int b) {
    if (b == 0) {
        // Handle modulus by zero error
        return 0; // or some error code
    }
    return a % b;
}
#endif