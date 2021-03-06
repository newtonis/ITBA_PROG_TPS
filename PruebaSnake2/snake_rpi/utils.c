#include "utils.h"
#include <math.h>

#define DEF_SZ 10


int str_to_int(char *str,int *target){
    int j = 0;
    int good = 1;
    while (str[j] != '\0'){
        if (str[j] < '0' || str[j] > '9'){
            good = 0;
        }
        j++;
    }
    
    if (good){
        int i = 0;
        int ans = 0;
        while (str[i] != '\0'){
            ans *= 10;
            ans += str[i] - '0';
            i++;
        }
        *target = ans;
        return 0;
    }else{
        return 1;
    }
}
void init_empty_array(int *arr,int sz){
    int i;
    for (i = 0;i < sz;i++){
        arr[i] = 0;
    }
}
void int_to_str(int value,char *ans,int min_size){
    char aux[DEF_SZ];
    
    int i = 0;
    while (value > 0 || min_size > 0){
        min_size --;
        aux[i++] = (value%10)+'0';
        value /= 10;
    }
    i --;
    int j = 0;
    while (i >= 0){
        ans[j++] = aux[i--];
    }
    ans[j] = '\0';
}
/// make A be between b and c
int fix_value(int a,int b,int c){
    return min( max(a , b) , c);
}
void copy_str(char *a,char *b){
    int i = 0;
    while (a[i] != '\0'){
        b[i] = a[i];
        i++;
    }
}