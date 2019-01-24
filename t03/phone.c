#include <stdio.h>

int main() {
    int num;
    char s[10];
        
    while(scanf("%10s %d", s, &num) != EOF){
        if(num ==0){
            printf("%s\n", s);

        }else{
            printf("%c\n",(int) s[num]);

        }
   


    }

}
