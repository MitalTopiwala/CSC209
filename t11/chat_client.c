#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "socket.h"


#ifndef PORT
  #define PORT 50001
#endif
#define BUF_SIZE 128

int main(void) {
    int sock_fd = connect_to_server(PORT, "127.0.0.1");

    // Read input from the user, send it to the server, and then accept the
    // echo that returns. Exit when stdin is closed.
    char buf[BUF_SIZE + 1];
    while (1) {
        int num_read = read(STDIN_FILENO, buf, BUF_SIZE);
        if (num_read == 0) {
            break;
        }
        buf[num_read] = '\0';         // Just because I'm paranoid

        int num_written = write(sock_fd, buf, num_read);
        if (num_written != num_read) {
            perror("client: write");
            close(sock_fd);
            exit(1);
        }

        num_read = read(sock_fd, buf, BUF_SIZE);
        buf[num_read] = '\0';
        printf("Received from server: %s", buf);
    }

    close(sock_fd);
    return 0;
}
