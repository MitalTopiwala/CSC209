// TODO: Implement populate_array
/*
 * Convert a 9 digit int to a 9 element int array.
 */
int populate_array(int sin, int *sin_array) {
    if( sin%100000000 == 0 || sin%100000000 > 9){
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
    return 1;
}
