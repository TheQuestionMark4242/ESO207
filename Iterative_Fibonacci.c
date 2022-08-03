#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
const int eps = 1e-4;
const int MOD = 2021;

long long int iterative_fibonacci(long long int n){
    if(n == 0) return 0;
    long long int a = 0;
    long long int b = 1;
    n--;
    while(n--){
        b = a + b;
        a = b - a;
    }
    return b;
}

double timer(long long int n){
    clock_t start_t, end_t;
    double total_t;
    start_t = clock();
    for(int i = 1; i <= 1000; i++){
        iterative_fibonacci(n);            
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