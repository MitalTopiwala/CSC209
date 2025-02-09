#include <stdio.h>
// Add your system includes here.
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

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

const unsigned int MAX_PID_LEN = 60;//can change later
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

//    printf("%s\n", procfile);

    // Your implementation goes here.
    
    //0. create the root node with name and pid
    struct TreeNode rn;
    rn.pid = pid;
    strcpy(rn.name, procfile); 
    
    root = malloc(sizeof(struct TreeNode*));
    if(root == NULL){
        return 1;
    }        
    *root = &rn;
  
    //1. craete a list of children pidsand keep track of # of children
    char childfile[MAX_PATH_LENGTH + 1];
    if (snprintf(childfile, MAX_PATH_LENGTH + 1, "%s/%d/task/PID/children", PROC_ROOT, pid) < 0) {
        fprintf(stderr, "snprintf failed to produce a children filename\n");
        return 1;
    }

  //  printf("%s\n", childfile);

    struct stat buffer;
    if(lstat(childfile, &buffer) !=0){
        fprintf(stderr, "lstat failed to find file\n");
        return 1;
    }


    FILE* child_stream = fopen(childfile, "rb");
    int child = 0;
    int num_children = 0;
    int *children= malloc(sizeof(int)*100);//assuming max 100 children
    if (children == NULL){
        return 1;
    }

    if(fscanf(child_stream, "%d", &child) != 0){
        children[num_children] = child;
        num_children+=1;        
    } 
    fclose(child_stream);

    /*char buffer[MAX_PID_LEN+1];
    int num_children = 0;
    int *children= malloc(sizeof(int)*100);//assuming max 100 children
    int index = 0;
    while(snprintf(buffer, MAX_PID_LEN + 1, "%s/%d/task/PID/children", PROC_ROOT, pid)!=0){
        
        char *endptr;
        children[index] = (int)strtol(buffer,&endptr, 10);
        
       
        num_children++;
        index++;
        buffer[0] = '\0';//clear variable
    }
    */

    /*char buffer[(MAX_PID_LEN+1)*100];
    int num_children = 0;
    int *children= malloc(sizeof(int)*100);//assuming max 100 children
    char *token;
    char *rest = NULL;
    
    if(snprintf(buffer, (MAX_PID_LEN +1)*100, "%s/%d/task/PID/children", PROC_ROOT, pid)!=0){
        for (token = strtok_r(buffer, " ", &rest); token != NULL; token = strtok_r(NULL, " ", &rest)){
         char * end_ptr;
         children[num_children] = (int)strtol(token,&end_ptr, 10);
       
         printf("%d\n", children[num_children]);
         num_children +=1;
       
         }

    }

    */


   /* char buffer[MAX_PID_LEN+1];
    int num_children = 0;
    int *children= malloc(sizeof(int)*100);//assuming max 100 children
    
    while(lstat(
    //2. Base Case
    if (num_children ==0){
        return 0;
    }    
    */
    //3.Cycle though children and recursivly create tree
    struct TreeNode* previous_child = malloc(sizeof(struct TreeNode));
    if(previous_child == NULL){
        return 1;
    }
    for(int i = num_children-1; i>=0; i--){
        struct TreeNode** subtree = NULL;//malloc(sizeof(struct TreeNode*));
        generate_ptree(subtree, children[i]);//might have to cats to type pid_t
        (*subtree)->next_sibling = previous_child;
        previous_child = *subtree;
    }
    (*root)->child_procs = previous_child;

      
    return 0;
}
/*
//return the nuber of TreeNodes added to list
int insert_in_list(struct TreeNode **list,int len_list, struct TreeNode *to_insert){
    //TODO; add to list with all its info without linking it in if no siblings
    //      or children found
    //restucture child-procs
    while(to_insert->child_procs != NULL){
        for (int i =0; i<len_list; i++){
            if(list[i]->pid == to_insert->child_procs->pid){
                //use inserting in the middle of a linked list techniques from 
                //PCRS
                char buffer[MAX_PID_LEN+1];
                struct TreeNode next_child;
                
                    struct TreeNode *curr = (.pid = 

                }
                
                
            }
        
        to_insert->child_procs = to_insert->child_procs->child_procs;  
    }
    //restructure siblings
    while(to_insert->next_sibling != NULL){
        for (int i =0; i<len_list; i++){
            if(list[i]->pid == to_insert->next_sibling->pid){
                //use inserting in the middle of a linked list techniques from 
                //PCRS 
            }
        }
        to_insert->next_sibling = to_insert ->next_sibling->next_sibling;
    }
} 
*/

  
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
    //TODO: check command line arguments and emit appropriate error message
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
