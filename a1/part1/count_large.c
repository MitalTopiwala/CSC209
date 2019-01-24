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
    
    char perm[9];
    int size;
    char name[31];
    while (scanf("%[9]s %*d %*s %*s %d %*d %*s %*s %s", perm, size, name ) {
    }   
    
    // TODO: Process command line arguments.
    int total =0;
    if (argc == 2) {
        //print number of files that are larger than argv[1] in size
     
        while(scanf("%*s %*d %*s %*s %d %*d %*s %*s %s",size,name) != EOM){
            if (size > argv[1]){
                total+=1;
            }
        }
                

    }else{
        //print numbers of files that are larger than argv[1] in size, and             have at least the permissions specified in argv[2]
        while(scanf("%[9]s %*d %*s %*s %d %*d %*s %*s %s",perm,size,name)!=EOM){

    // TODO Call check permissions and then print the returned value.
            if(size > argv[1] && check_permission(argv[2], perm)==0){
                total+=1;
            }
        }
               
    }
    printf("%d", total);
    return 0;
}
