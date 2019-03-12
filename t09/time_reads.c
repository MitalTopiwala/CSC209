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


int main(int argc, char ** argv) {
    if (argc != 3) {
        fprintf(stderr, "Usage: time_reads s filename\n");
        exit(1);
    }
    seconds = strtol(argv[1], NULL, 10);

    FILE *fp;
    if ((fp = fopen(argv[2], "r+")) == NULL) {    // Read+Write for later ...
      perror("fopen");
      exit(1);
    }

    /* In an infinite loop, read an int from a random location in the file
     * and print it to stderr.
     */
    for (;;) {


    }

    return 1;  //something is wrong if we ever get here!
}

