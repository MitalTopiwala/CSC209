#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
    Complete this program by writing the function strip_q_marks that takes
    a single string and returns an integer.

    The function should modify the string to remove any trailing question marks
    and return the number of question marks that were removed.

    Examples
    original sentence       modified sentence       return value
    =============================================================
    "Hello? World???"       "Hello? World"          3
    "What..?"               "What.."                1
    "Apples?..?"            "Apples?.."             1
    "Coffee"                "Coffee"                0
*/

// Write the function strip_q_marks here
int strip_q_marks(char*str){
    //int cut_i = 0;
    int ret_val = 0;
    for(int i =0; i<strlen(str); i++){
        if(str[i]== '?'){
            //cut_i = i;
            int next = 1;
            while(str[i+next]=='?'){
                next +=1;
            }
            if(str[i+next]== '\0'){
                ret_val = strlen(str) - i;
                str[i] = '\0';
                return ret_val;
            }

        }
    }
    return ret_val;
}

int main(int argc, char **argv) {
    // Do not change this main function.
    if(argc != 2) {
        fprintf(stderr, "Usage: strip message\n");
        exit(1);
    }
    int result = strip_q_marks(argv[1]);
    printf("%s %d", argv[1], result);
    return 0;
}
