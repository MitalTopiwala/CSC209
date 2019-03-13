#include <stdio.h>

#include "eratosthenes.h"

int filter(int n, int readfd, int writefd) {
    // TODO: Complete
    int value;
    int count = 0;
    while (read(readfd, &value, sizeof(int)) != 0){
        count += 1;

        if((n%value) != 0){//value can be any number ffrom 2 to n
            //value is NOT a multiple of n, so write it to writefd
            int writefd_ret = write(writefd, &value, sizeof(int));
            if(writefd_ret == -1){
                return 1;
            }
        }
    }

    if (count == 0){
        //this means that readfd was empty
        return 1;
    }
    return 0;
}

