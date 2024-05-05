#include <stdio.h> 
#include <stdlib.h>
#include <time.h>
#define N 1<<10
  
int mat1[N][N];
int mat2[N][N];
int res[N][N]; // To store result 

int main() 
{ 
    
    int i, j, k;
    clock_t start, end;

    double cpu_time;

    for (int i = 0; i < N; i++) { 
		for (int j = 0; j < N; j++) { 
			mat1[i][j] = rand() % 10; 
			mat2[i][j] = rand() % 10; 
		} 
	} 
	
    start = clock();
   // multiply(mat1, mat2, res);
    for (j = 0; j < N; j++) 
    { 
        for (i = 0; i < N; i++) 
        { 
            res[i][j] = 0; 
            for (k = 0; k < N; k++) 
                res[i][j] += mat1[i][k]*mat2[k][j]; 
        } 
    } 
  
    printf("DONE\n");
    end = clock();
    cpu_time = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("CPU Time = %f\n", cpu_time);
    
    return 0; 
} 
