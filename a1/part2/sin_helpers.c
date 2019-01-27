// TODO: Implement populate_array
/*
 * Convert a 9 digit int to a 9 element int array.
 */
int populate_array(int sin, int *sin_array) {
    //check if sin has less tahn or more tahn 9 digits
    if( sin/100000000 <1  || sin/100000000 > 9){
        return 1;
    }
    for(int i = 0; i<9;i++){
        int last_digit = (sin/10 - sin%10)*10;
        sin_array[8-i] = last_digit;
        sin = sin%10;
    }
    return 0;
}

// TODO: Implement check_sin
/* 
 * Return 0 (true) iff the given sin_array is a valid SIN.
 */
int check_sin(int *sin_array) {
    int sum = 0;
    
    if (sin_array[0]==0){
        return 1;
    }

    for(int i=0; i<9; i++) {
        if(sin_array[i]%10 !=0){
            sum += 1 +sin_array[i]-10;
        }else{
            sum+=sin_array[i];
        }
    }
    
    if(sum%10 ==0){
        return 0;
    }
        
    
    return 1;
}
