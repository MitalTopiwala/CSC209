#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#include "socket.h"
#include "jobprotocol.h"


#define QUEUE_LENGTH 5

#ifndef JOBS_DIR
    #define JOBS_DIR "jobs/"
#endif

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

