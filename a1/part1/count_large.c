#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// TODO: Implement a helper named check_permissions that matches the prototype below.
int check_permissions(char * standard, char * tocheck) {
    char skip = '-';
    for (int i=1;i<10;i++){
        if (!(standard[i-1] == skip)){
            if(!(standard[i-1]==tocheck[i])){
                //printf("%c %c", standard[i-1], tocheck[i]);
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
    
    char perm[11];
    int size;
    char name[31];   
    int min_size = strtol(argv[1], NULL, 10);

    // TODO: Process command line arguments.
    int total =0;
    scanf("%*s %*d");//skips the first line

    if (argc == 2) {
        //print number of files that are larger than argv[1] in size
     
        while(scanf("%*s %*d %*s %*s %d %*d %*s %*s %s",&size,name) != EOF){
            
            if (size > min_size){
                total+=1;
            }
        }
                

    }else{
        //print numbers of files that are larger than argv[1] in size, and             have at least the permissions specified in argv[2]
        while(scanf("%s %*d %*s %*s %d %*d %*s %*s %s",perm,&size,name)!=EOF){
            
    // TODO Call check permissions and then print the returned value.
            if(size > min_size && (check_permissions(argv[2], perm)==0)){
                total+=1;
            }
        }
               
    }
    printf("%d", total);
    return 0;
}
