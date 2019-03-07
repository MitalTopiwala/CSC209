#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAXLINE 256
#define MAX_PASSWORD 10

#define SUCCESS "Password verified\n"
#define INVALID "Invalid password\n"
#define NO_USER "No such user\n"

int main(void) {
  char user_id[MAXLINE];
  char password[MAXLINE];

  if(fgets(user_id, MAXLINE, stdin) == NULL) {
      perror("fgets");
      exit(1);
  }
  
  if(fgets(password, MAXLINE, stdin) == NULL) {
      perror("fgets");
      exit(1);
  }
  
  int fd[2];
  if(pipe(fd) == -1){
      perror("pipe");
  }
  int r = fork();

  if (r > 0){
      close(fd[0]);
      
      //write input from stdin to pipe
      if (write(fd[1], user_id, MAX_PASSWORD) == -1) {
          perror("write to pipe");
      }
      if (write(fd[1], password, MAX_PASSWORD) == -1) {
          perror("write to pipe");
      }
      close(fd[1]);
      
     
      //wait for child to return value
      int status=0;
      wait(&status); 
          if(WIFEXITED(status) != 0){
              int ret_val = WEXITSTATUS(status);//return value of validate   

              if (ret_val == 0) {
                    printf("%s", SUCCESS);
               }else if(ret_val == 2 || ret_val == 1) {
                    printf("%s", INVALID);
               }else if(ret_val ==3){
                    printf("%s", NO_USER);
               }
           }
      
      
      
  } else if(r == 0){
      close(fd[1]);
      //give pipe stuff to validate as command arguements
      dup2(fd[0], fileno(stdin));
      close(fd[0]);
      execl("./validate", "validate", NULL);


      //

  }   




  return 0;
}
