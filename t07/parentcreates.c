#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char **argv) {

	int i;
	int n = 0;
	int num_kids;

	if (argc != 2) {
		fprintf(stderr, "Usage: parentcreates <numkids>\n");
		exit(1);
	}

	num_kids = strtol(argv[1], NULL, 10);

	for (i = 0; i < num_kids; i++) {
            for(int j = i; j<num_kids; j++){
                int ih = i;
                int jh = j;
		i = num_kids;
                j = num_kids;
                n = fork();
                if(n > 0){
                    i = ih;
                    j = jh;
                }
                
                //if (n == 0){
                    
                //}
                
		if (n < 0) {
			perror("fork");
			exit(1);
		}
 		printf("pid = %d, ppid = %d, i = %d\n", getpid(), getppid(), i);
	    }
        }

	return 0;
}
