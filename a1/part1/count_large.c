#include <stdio.h>
#include <stdlib.h>


// TODO: Implement a helper named check_permissions that matches the prototype below.
int check_permissions(char * standard, char * tocheck) {
    for (i=0;i<9;i++){
        if (!(standard[i]=="-")){
            if(!(standard[i]==tocheck[i])){
                return 1;
            }
        }
    }
    return 0;
}


int main(int argc, char** argv) {
    if (!(argc == 2 || argc == 3)) {
        fprintf(stderr, "USAGE:\n\tcount_large size [permissions]\n");
        return 1;
    }

    // TODO: Process command line arguments.
    if (argc == 2) {
        //print number of files that are larger than argv[0][0] in size
    }else{
        //print numbers of files that are larger than argv[0][0] in size, and             have at least the permissions specified in argv[1][0]
    
    // TODO Call check permissions and then print the returned value.
         
    }
    return 0;

