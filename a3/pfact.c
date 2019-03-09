#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <math.h>

#include "eratosthenes.h"


int main(int argc, char *argv[]) {
    // Turning off sigpipe
    if (signal(SIGPIPE, SIG_IGN) == SIG_ERR) {
        perror("signal");
        exit(1);
    }

    // Your solution below ...
    if(argc !=2){
        fprintf(stderr, "Usage:\n\tpfact n\n");
    }


    
    return 0;
}

void primefact(int n){
    //first create a pipe
    int fd[2];
    int pipe_ret = pid(fd);
    if(pipe_ret == -1){//check for error
        perror("pipe");
        exit(1);
    } 
    //Now fork
    int fork_ret = fork();
    if(f_out == -1){//checl for error
        perror("fork");
        exit(1);
    }
    
    if(fork_ret > 0){
    //we are in the parent

    }else{
    //we are in the child


    }



}
