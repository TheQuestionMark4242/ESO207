#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
const int eps = 1e-4;
const int MOD = 2021;
typedef struct {
    int rows;
    int cols;
    double * data;
} matrix;
matrix * newMatrix(int rows, int cols) {
    if (rows <= 0 || cols <= 0) return NULL;
    matrix * m = (matrix *) malloc(sizeof(matrix));
    m->rows = rows;
    m->cols = cols;
    m->data = (double *) malloc(rows*cols*sizeof(double));
    for (int i = 0; i < rows*cols; i++)
        m->data[i] = 0.0;
  return m;
}
int deleteMatrix(matrix * mtx) {
    if (!mtx) return -1;
    free(mtx->data);
    free(mtx);
    return 0;
}
#define ELEM(mtx, row, col) \
    mtx->data[(col-1) * mtx->rows + (row-1)]


int product(matrix * mtx1, matrix * mtx2, matrix * prod) {
    if (!mtx1 || !mtx2 || !prod) return -1;
    if (mtx1->cols != mtx2->rows ||
        mtx1->rows != prod->rows ||
        mtx2->cols != prod->cols)
    return -2;

    int row, col, k;
    for (col = 1; col <= mtx2->cols; col++)
        for (row = 1; row <= mtx1->rows; row++) {
        double val = 0.0;
        for (k = 1; k <= mtx1->cols; k++)
            val += ELEM(mtx1, row, k) * ELEM(mtx2, k, col);
        ELEM(prod, row, col) = val;
    }
  return 0;
}
matrix * copyMatrix(matrix * mtx) {
    if (!mtx) return NULL;
    matrix * cp = newMatrix(mtx->rows, mtx->cols);
    memcpy(cp->data, mtx->data, mtx->rows * mtx->cols * sizeof(double));
    return cp;
}

long long int matrix_fibonacci(long long int n){
    if(n == 0 || n == 1) return n;

    matrix* a = newMatrix(2, 2);
    matrix* res = newMatrix(2, 2);
    ELEM(a, 1, 1) = ELEM(a, 2, 1) = ELEM(a, 1, 2) = 1;
    ELEM(a, 2, 2) = 0;
    ELEM(res, 1, 1) = ELEM(res, 2, 2) = 1;
    ELEM(res, 1, 2) = ELEM(res, 2, 1) = 0;
    
    n--;
    while(n){
        matrix* temp = newMatrix(2, 2);
        if(n&1){
            product(a, res, temp);
            res = copyMatrix(temp);
        }
        product(a, a, temp);
        a = copyMatrix(temp);
        n /= 2;
    }
    deleteMatrix(a);
    deleteMatrix(res);
    return ELEM(res, 1, 1);
}
double timer(long long int n){
    clock_t start_t, end_t;
    double total_t;
    start_t = clock();
    for(int i = 1; i <= 1000; i++){
        matrix_fibonacci(n);            
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