#include <unistd.h>

#include "eratosthenes.h"

pid_t make_stage(int n, int read_fd, int **fds) {
    // TODO: Complete
    //we are in the child process
    int *actual_fds = *fds;
    close(fd[1]);

    int fd2[2];

    int pipe_ret = pipe(fd2);
    if(pipe_ret == -1){
        //error
        exit(1);//?
    }

    int fork_ret = fork();
    if(fork_ret == -1){
        //perror
        exit(1);
    }
    if (fork_ret >0){
    //we are in the childs (perent)




    }else{
    //we are in the childs child




   }
    
}
