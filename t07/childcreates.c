#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char **argv) {

	int i;
	int n;
	int num_kids;

	if (argc != 2) {
		fprintf(stderr, "Usage: childcreates <numkids>\n");
		exit(1);
	}

	num_kids = strtol(argv[1], NULL, 10);

	for (i = 0; i < num_kids; i++) {
                int ih = i;
                i = num_kids -1;
		n = fork();

		if (n < 0) {
			perror("fork");
			exit(1);
		}
                int delay = 5;
                if(n == 0){
                        i = ih;
                }else{
                        wait(&delay);
                }

 		printf("pid = %d, ppid = %d, i = %d\n", getpid(), getppid(), i);
	}

	return 0;
}
