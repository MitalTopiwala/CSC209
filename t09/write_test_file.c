#include <stdio.h>
#include <stdlib.h>

int main(int argc,  char ** argv){

FILE * file = fopen(argv[1], "w");
int nums[100];
//populate array 
for(int i = 0; i <100; i++){
    nums[i] = rand();

}

//write array to file
fwrite(nums, sizeof(int), 100, file); 

return 0;

}
