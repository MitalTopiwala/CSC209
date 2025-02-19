#include <stdio.h>
#include <stdlib.h>

/*
 * Write a void function invest that takes your money and multiplies it by the given rate.
 */
void invest(double*principle, double rate) {
    *principle = *principle * rate;
}

/*
 * NOTE: don't change the main function!
 * Sample usage:
 * $ gcc -Wall -std=gnu99 -g -o invest invest.c
 * $ ./invest 10000 1.05
 * 10500.00
 */
int main(int argc, char **argv) {
    // NOTE: No error checking performed on command line arguments.
    // Read in the command-line arguments and convert the strings to doubles
    double principal = strtod(argv[1], NULL);
    double rate = strtod(argv[2], NULL);

    // Call invest to make you more money
    invest(&principal, rate);

    printf("%.2f\n", principal);
    return 0;
}
