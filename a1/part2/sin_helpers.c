//#include <stdio.h>
// TODO: Implement populate_array
/*
 * Convert a 9 digit int to a 9 element int array.
 */
int populate_array(int sin, int *sin_array) {
    //check if sin has less tahn or more tahn 9 digits
    if( sin/100000000.0 <1  || sin/100000000.0 >= 10){
        return 1;
    }
    for(int i = 8; i>=0;i--){
        int last_digit = sin%10;
        sin_array[i] = last_digit;
        sin = sin/10.0 - (sin%10)/10.0;
    }
    return 0;
}

// TODO: Implement check_sin
/* 
 * Return 0 (true) iff the given sin_array is a valid SIN.
 */
int check_sin(int *sin_array) {
    int sum = 0;
    
    int to_multiply[9] = {1,2,1,2,1,2,1,2,1};
    for(int i=0; i<9; i++) {
        int multi_num = sin_array[i] * to_multiply[i];

        if(multi_num >=10){
            sum += 1 +(multi_num-10);
        }else{
            sum+=multi_num;
        }
//        printf("%d", sum);
    }
    
    if(sum%10 ==0){
        return 0;
    }
        
    return 1;
}
