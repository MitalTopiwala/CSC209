#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <signal.h>
#include <sys/time.h>


// Message to print in the signal handling function. 
#define MESSAGE "%ld reads were done in %ld seconds.\n"


/* Global variables to store number of read operations and seconds elapsed.
 * These have to be global so that signal handler to be written will have
 * access.
 */
long num_reads = 0, seconds;


void handler(int code){
    fprintf(stderr, MESSAGE, num_reads, seconds);
//    printf("SIGPROF");
    exit(1);
}




int main(int argc, char ** argv) {
    if (argc != 3) {
        fprintf(stderr, "Usage: time_reads s filename\n");
        exit(1);
    }
    seconds = strtol(argv[1], NULL, 10);

    //setup sigaction struct
    struct sigaction newsig;
    sigemptyset(&newsig.sa_mask);
    newsig.sa_flags = 0;
    newsig.sa_handler = handler;
    //call hadle function when SIGPROF is envoked 
    if(sigaction(SIGPROF, &newsig, NULL)== -1) exit(1);
    //set up SIGPROF?
    struct itimerval timer;
    timer.it_value.tv_sec = 0;
    timer.it_value.tv_usec = seconds;
    setitimer(ITIMER_PROF, &timer , NULL);
    

    FILE *fp;
    if ((fp = fopen(argv[2], "r+")) == NULL) {    // Read+Write for later ...
      perror("fopen");
      exit(1);
    }

    /* In an infinite loop, read an int from a random location in the file
     * and print it to stderr.
     */
    //int rand_value[999999];
    int rand_val = 0;
    for (int i = 0 ; i >= 0; i ++) {
        int position = rand()%100;
        fseek(fp, position, SEEK_SET);
        fread(&rand_val, sizeof(int), 1, fp);
        num_reads +=1;
        printf("%d \n", rand_val);
    }

    return 1;  //something is wrong if we ever get here!
}

