#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int populate_array(int, int *);
int check_sin(int *);


int main(int argc, char **argv) {
    // TODO: Verify that command line arguments are valid.
    if (argc != 2 || strlen(argv[1]) != 9){
        printf("Invalid SIN");
        return 1;
    }
    // TODO: Parse arguments and then call the two helpers in sin_helpers.c
    // to verify the SIN given as a command line argument.
    int *sin = malloc(sizeof(int)*9);
    int given_sin = *argv[1];
    int pa = populate_array(given_sin, sin);
    int sh = check_sin(sin);
//    printf("%d %d", pa, sh);
    if (sh+pa!=0){
        printf("Invalid SIN");
        return 1;
    }
    free(sin);
    printf("Valid SIN");
    return 0;
}
