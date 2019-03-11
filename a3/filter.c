#include <stdio.h>

#include "eratosthenes.h"

int filter(int n, int readfd, int writefd) {
    // TODO: Complete
    int value;
    while (int readfd_ret = read(readfd, &value, sizeof(int)) != -1){
     

        if((n%value) != 0){
            int writefd_ret = write(writefd, &value, sizeof(int));
        }
    }
    return 0;
}

