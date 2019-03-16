#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <math.h>

#include "eratosthenes.h"

void primefact(int n){
    //first create a pipe
    int fd[2];
    int pipe_ret = pipe(fd);
    if(pipe_ret == -1){//check for error in creating pipe
        perror("pipe");
        exit(1);
    } 
    //Now fork
    int fork_ret = fork();
    if(fork_ret == -1){//checl for error in creating fork

        perror("fork");
        exit(1);
    }
    
    if(fork_ret > 0){
    //we are in the parent
        close(fd[0]);
    
    //write values from 1 to n into pipe
        for(int i = 2; i<=n; i++){
            int write_ret  = write(fd[1], &i, sizeof(int));
            if(write_ret == -1){
            //what do i do? raise an error?then do i exit?
            perror("writing to pipe");
            exit(1);
            }


        } 

        //wait for child to return value
        int status=0;
        wait(&status);
        if(WIFEXITED(status) != 0){
            int result = WEXITSTATUS(status);//return value of validate   
            printf("Number of filters = %d\n", result);
             
         }
    

    }else{
    //we are in the child
    //call the make_stage() function?
      //the make_stage function will make new file descriptors, use one of 
      //them as third arguement for filter
    int **fd2 = malloc(sizeof(int)*2);
    int stage_ret = make_stage(n, fd[0],fd2 );
    if(stage_ret == 255){
        exit(2);
    }
    //filter(m, f[0], );
    


    }



}

int main(int argc, char *argv[]) {
    // Turning off sigpipe
    if (signal(SIGPIPE, SIG_IGN) == SIG_ERR) {
        perror("signal");
        exit(1);
    }

    // Your solution below ...
    //chcek that correct arguements are given
        //get n value 
    if(argc != 2){
        fprintf(stderr, "Usage:\n\tpfact n\n");
    }
    char** temp = NULL;
    int n_val = strtol(argv[1],temp, 10); 
   
    if(n_val < 0 ){
        fprintf(stderr, "Usage:\n\tpfact n\n");
    }
    

    //Call primefact helper function
    //for(int i = 0;  
    primefact(n_val);

    return 0;
}
