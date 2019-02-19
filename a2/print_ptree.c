#include <stdio.h>
#include <stdlib.h>

#include "ptree.h"


int main(int argc, char **argv) {
    // TODO: Update error checking and add support for the optional -d flag
    // printf("Usage:\n\tptree [-d N] PID\n");
    if(argc != 2 || argc !=4){
        printf("Usage:\n\tptree [-d N] PID\n");
        return 1;
    }
    if (argc ==2){    
    // NOTE: This only works if no -d option is provided and does not
    // error check the provided argument or generate_ptree. Fix this!
        struct TreeNode *root = NULL;
        generate_ptree(&root, strtol(argv[1], NULL, 10));
        print_ptree(root, 0);
    
        return 0;
    }else{
        struct TreeNode *root = NULL;
        generate_ptree(&root, strtol(argv[1], NULL, 10));
        print_ptree(root, strtol(argv[3], NULL, 10));
    
        return 0;


   }
}

