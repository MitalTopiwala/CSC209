#include <stdio.h>
// Add your system includes here.

#include "ptree.h"

// Defining the constants described in ptree.h
const unsigned int MAX_PATH_LENGTH = 1024;

// If TEST is defined (see the Makefile), will look in the tests 
// directory for PIDs, instead of /proc.
#ifdef TEST
    const char *PROC_ROOT = "tests";
#else
    const char *PROC_ROOT = "/proc";
#endif


/*
 * Creates a PTree rooted at the process pid. The root of the tree is
 * placed in root. The function returns 0 if the tree was created 
 * successfully and 1 if the tree could not be created or if at least
 * one PID was encountered that could not be found or was not an 
 * executing process.
 */
int generate_ptree(struct TreeNode **root, pid_t pid) {
    // Here's a trick to generate the name of a file to open. Note 
    // that it uses the PROC_ROOT variable
    char procfile[MAX_PATH_LENGTH + 1];
    if (snprintf(procfile, MAX_PATH_LENGTH + 1, "%s/%d/exe", PROC_ROOT, pid) < 0) {
        fprintf(stderr, "snprintf failed to produce a filename\n");
        return 1;
    }

    printf("%s\n", procfile);

    // Your implementation goes here.
    return 0;
}


/*
 * Prints the TreeNodes encountered on a preorder traversal of an PTree
 * to a specified maximum depth. If the maximum depth is 0, then the 
 * entire tree is printed.
 */
void print_ptree(struct TreeNode *root, int max_depth) {
    // Here's a trick for remembering what depth (in the tree) you're at
    // and printing 2 * that many spaces at the beginning of the line.
    static int depth = 0;
    //printf("%*s", depth * 2, "");

    // Your implementation goes here.
    if(root == NULL ||max_depth ==-1){
    //TODO: generate ptree so this stops when  root == NULL 
    }else{
        while(root != NULL){
            //First collect and print info about root
            printf("%*s", depth * 2, "");
            if(root->name[0] == '\0'){//TODO: generate ptree accordingly 
                printf("%d\n", root->pid);
            }else{
                printf("%d: %s\n", root->pid, root->name);
            }

            //Then, Traverse child_procs linked list and recursivly call the 
            //function on each of them (remember to decrement max_depth)
            struct TreeNode *curchild = root->child_procs;
            depth +=1;
            if (max_depth ==1){
                print_ptree(curchild, -1);//to allow 0 param to be special
            }else if(max_depth ==0){
                print_ptree(curchild, max_depth);//to mantain 0
            }else{
                print_ptree(curchild, max_depth-1);//decrease normally otherwise
            }
            depth -=1;            
            
       
            root = root->next_sibling;//done here and moving on to next sibling
        }
    }
}
