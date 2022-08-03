#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
const int eps = 1e-4;
const int MOD = 2021;

long long int recursive_fibonacci(long long int n){
    if(n == 0 || n == 1) return n;
    else
        return (recursive_fibonacci(n-1)+recursive_fibonacci(n-2)) % MOD;
}
double timer(long long int n){
    clock_t start_t, end_t;
    double total_t;
    start_t = clock();
    for(int i = 1; i <= 1000; i++){
        recursive_fibonacci(n);            
    }
    end_t = clock();
    total_t = (double) (end_t-start_t)/CLOCKS_PER_SEC;
    
    return total_t;
}
int main(){
    long long int n;
    scanf("%lld", &n);
    printf("%.6lf", timer(n)/1000);
    return 0;
}