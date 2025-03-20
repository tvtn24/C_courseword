#include<stdio.h>
#include"histogram.h"

void histogram(int *x, double *y, int n, int width);

int main(){
    // test histogram function
    int x[] = {0, 1, 2, 3, 4, 5};
    double y[] = {12.5, 6.4, 10, 7.6, 8, 13};
    histogram(x, y, 6, 30);
    return 0;
}