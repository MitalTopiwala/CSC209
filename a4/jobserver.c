#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#include <sys/wait.h>

#include "socket.h"
#include "jobprotocol.h"


#define QUEUE_LENGTH 5

#ifndef JOBS_DIR
    #define JOBS_DIR "jobs/"
#endif

/*
 * Search the first n characters of buf for a network newline (\r\n).
 * Return one plus the index of the '\n' of the first network newline,
 * or -1 if no network newline is found.
 * Definitely do not use strchr or other string functions to search here. (Why not?)
 */
int find_network_newline(const char *buf, int inbuf) {
    //int found_r = -1;
    for (int i = 0; i <inbuf-1; i++){
        if(buf[i] == '\r' && buf[i+1] == '\n'){
            return i+2;
        }
    }
    return -1;
}

void jobs(pid_t* pid_lst){
    int num_pids = (sizeof(pid_lst) / sizeof(pid_lst[0]));
    if (num_pids == 0){
      printf("[SERVER] No currently running jobs");
    }else{
      char print_msg[10*MAX_JOBS];
      strcpy(print_msg, "[SERVER]");
      for(int i = 0; i < num_pids; i++){
        //convert pid to char and concat it to print_msg
        char pid_char[10];
        snprintf(pid_char, 10, " %d", (int) pid_lst[i]);
        strcat(print_msg, pid_char);  

      }

    }

}

int main(void) {
    // This line causes stdout and stderr not to be buffered.
    // Don't change this! Necessary for autotesting.
    setbuf(stdout, NULL);
    setbuf(stderr, NULL);

    struct sockaddr_in *self = init_server_addr(PORT);
    int listenfd = setup_server_socket(self, QUEUE_LENGTH);


    /* TODO: Initialize job and client tracking structures, start
     * accepting connections. Listen for messages from both clients
     * and jobs. Execute client commands if properly formatted. 
     * Forward messages from jobs to appropriate clients. 
     * Tear down cleanly.
     */
     pid_t pids[MAX_JOBS];
     int num_jobs = 0; //make sure this is always < MAXJOBS
//     char* names[MAX_JOBS];

     //start accepting connections
     while(1){
       int fd = accept_connection(listenfd);
       if(fd < 0){
         continue;
       }

       

         // Receive messages
        char buf[BUFSIZE] = {'\0'};
        int inbuf = 0;           // How many bytes currently in buffer?
        int room = sizeof(buf);  // How many bytes remaining in buffer?
        char *after = buf;       // Pointer to position after the data in buf

        int nbytes;
        while ((nbytes = read(fd, after, room)) > 0) {
            // Step 1: update inbuf (how many bytes were just added?)
            inbuf+= nbytes;

            int where;

            // Step 2: the loop condition below calls find_network_newline
            // to determine if a full line has been read from the client.
            // Your next task should be to implement find_network_newline
            // (found at the bottom of this file).
            //
            // Note: we use a loop here because a single read might result in
            // more than one full line.
            while ((where = find_network_newline(buf, inbuf)) > 0) {
                // Step 3: Okay, we have a full line.
                // Output the full line, not including the "\r\n",
                // using print statement below.
                // Be sure to put a '\0' in the correct place first;
                // otherwise you'll get junk in the output.
                // (Replace the "\r\n" with appropriate characters so the
                // message prints correctly to stdout.)
          
                if(where+1 > BUFSIZE){//if command os larger than BUFSIZE characters
                  perror("*(SERVER)* Buffer from job 1%d is full. Aborting job.");
                  exit(1);
                }

                buf[where-2] = '\0';//Q: do i have to move the other values forward(and remove the '\n'?
                //now add that job to uir lists

                
                num_jobs += 1;
                if(num_jobs > MAX_JOBS){//check to make sure we dont exceed MAXJOBS
                  perror("[SERVER] MAXJOBS exceeded");
                  exit(1);
                }
                
                //TODO: exectute job now (and add pid to pid array)
                      //1. job name and argyements are in buf right now, seperated by spaces. seperate them into an array
                /*
                char* job_command[BUFSIZE];// job name and arguemnts will be stored in this array
                 
                char delin[] = " ";
                char *ptr = strtok(buf, delin);
                int i = 0;
                while(ptr != NULL){
                   job_command[i] = ptr;
                   ptr = strtok(NULL, delin);
                   i += 1;
                }
                */

                 //2. use exec to actully execite the job_command[0] job (AND add pid to array)

                char exe_file[BUFSIZE];//job name +arguements
                //snprintf(exe_file, BUFSIZE, "%s%s", JOBS_DIR, buf);
                      //TODO: how do i call the exe_file job with its arguement????
                      int fd[2];
                      if(pipe(fd) == -1){
                        perror("pipe");
                      }
                      int r = fork();

                      if (r > 0){
                        //IN PARENT 
                        // DO I HAVE TO ADD A WHILE LOOP BEFORE I PIPE(and AfER I make the exe_file)? i think YES
                        close(fd[0]);

                        //write exec_file to pipe
                        if (write(fd[1], exe_file, BUFSIZE) == -1) {
                          perror("write to pipe");
                        }
                     
                        close(fd[1]);

                        //TODO: output "[SERVER] Job %d created" where %d is the PID of the created job.


                        //wait for child to return value
                        int status=0;
                        wait(&status);
                        if(WIFEXITED(status) != 0){
                           int ret_val = WEXITSTATUS(status);//return value of child job
                           if(ret_val == -1){
                            //do i have to handle?
                           }   
                        }

                       } else if(r == 0){
                         //IN CHILD 
                         close(fd[1]);
                         //read from pipe
                         char* job_read = NULL;
                         read(fd[0], job_read, BUFSIZE);

                         //give pipe stuff to validate as command arguements
                         char* job_command[BUFSIZE];// job name will be stored in this array

                         char delin[] = " ";
                         char *ptr = strtok(job_read, delin);
                         int i = 0;
                         while(ptr != NULL){
                           job_command[i] = ptr;
                           ptr = strtok(NULL, delin);
                           i += 1;
                         }
      
                         
                         //Move the pointer in fd[0] to point to the first arguemnt of job
                         //the code below is if we are giving the arguements in stdin
                         /*fseek(fd[0], sizeof(job_name), SEEK_SET);

                         dup2(fd[0], fileno(stdin));
                         close(fd[0]);
                         */

                         //check to see if job_command[0] is 'jobs' and in that case add arguemnt pids list
                         if(strcmp(job_command[0],  "jobs") == 0){
                           jobs(pids);

                         }else{

                           char exec_job_name[BUFSIZE+2];
                           snprintf(exec_job_name, BUFSIZE, "%s/%s", JOBS_DIR, job_command[0]);
                           //strcpy(exec_job_name, "./");
                           //strcat(exec_job_name, job_command[0]);

                           int num_arg = (sizeof(job_command)/sizeof(job_command[0])) -1;
                         
                           if(num_arg == 0){
                             execl(exec_job_name, job_command[0], NULL);

                           }else if(num_arg == 1){
                             execl(exec_job_name, job_command[0], job_command[1], NULL);

                           }else if(num_arg == 2){
                             execl(exec_job_name, job_command[0], job_command[1], job_command[2], NULL);

                           }//....how many arguements can it have??
                         }
                         // CHILD PROCESS DONE FOR A4***
   

                       }


                //TODO: what do i dp after i have exectuted the job??




                // Note that we could have also used write to avoid having to
                // put the '\0' in the buffer. Try using write later!

                // Step 4: update inbuf and remove the full line from the buffer
                // There might be stuff after the line, so don't just do inbuf = 0.

                // You want to move the stuff after the full line to the beginning
                // of the buffer.  A loop can do it, or you can use memmove.
                // memmove(destination, source, number_of_bytes)
                int number_of_bytes = inbuf-where;
                memmove(&buf[0], &buf[where], number_of_bytes);
                inbuf = number_of_bytes;
                                                                  



            }
            // Step 5: update after and room, in preparation for the next read.
            room = sizeof(buf) - inbuf;
            after = &buf[inbuf];


        }
        close(fd);
     }
    
          
    /* Here is a snippet of code to create the name of an executable
     * to execute:
     *
     * char exe_file[BUFSIZE];
     * snprintf(exe_file, BUFSIZE, "%s/%s", JOBS_DIR, <job_name>);
     */


    free(self);
    close(listenfd);
    return 0;
}


