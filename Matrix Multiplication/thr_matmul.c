#include <stdio.h> 
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#define N 1<<10
#define MAX_THREAD 4

int matA[N][N];
int matB[N][N];
int matC[N][N]; // To store result 
    
int step_i = 0; 

void* multi(void* arg) 
{ 
	int core = step_i++;

	// Each thread computes 1/4th of matrix multiplication 
	for (int i = core * N / 4; i < (core + 1) * N / 4; i++) 
		for (int j = 0; j < N; j++) 
			for (int k = 0; k < N; k++) 
				matC[i][j] += matA[i][k] * matB[k][j];
}

  
int main() 
{ 
    int i, j, k;
    clock_t start, end;

    double cpu_time;

  	for (int i = 0; i < N; i++) { 
		for (int j = 0; j < N; j++) { 
			matA[i][j] = rand() % 10; 
			matB[i][j] = rand() % 10; 
		} 
	} 
    start = clock();
    // multiply(mat1, mat2, res);
    // declaring four threads 
	pthread_t threads[MAX_THREAD]; 

	// Creating four threads, each evaluating its own part 
	for (int i = 0; i < MAX_THREAD; i++) { 
		int* p; 
		pthread_create(&threads[i], NULL, multi, (void*)(p)); 
	} 

	// joining and waiting for all threads to complete 
	for (int i = 0; i < MAX_THREAD; i++) 
		pthread_join(threads[i], NULL);

    printf("DONE\n");
    end = clock();
    cpu_time = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("CPU Time = %f\n", cpu_time);
    
    return 0; 
} 
