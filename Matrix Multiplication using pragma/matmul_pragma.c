#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 1<<10

int matA[N][N];
int matB[N][N];
int matC[N][N]; // To store result  

int main () {

	int	tid, nthreads, i, j, k, chunk;
	chunk = 64;                    /* set loop iteration chunk size */

	clock_t start, end;

    double cpu_time;
    
    start = clock();

	#pragma omp parallel shared(matA,matB,matC,nthreads,chunk) private(tid,i,j,k) 
	{
		tid = omp_get_thread_num();
  		if (tid == 0) {
 	   		nthreads = omp_get_num_threads();
    		printf("Starting matrix multiple example with %d threads\n",nthreads);
    		printf("Initializing matrices...\n");
    	}
  /*** Initialize matrices ***/
  	#pragma omp for schedule (static, chunk) 
  	for (i=0; i<N; i++) {
    	for (j=0; j<N; j++) { 
      		matA[i][j]= (i+j) % 10;
      		matB[i][j]= (i+j) % 10;
      	}
  	}
  /*** Do matrix multiply sharing iterations on outer loop ***/
  /*** Display who does which iterations for demonstration purposes ***/
  	printf("Thread %d starting matrix multiply...\n",tid);
  	#pragma omp for schedule (static, chunk)
  	for (i=0; i<N; i++) {
    	for(j=0; j<N; j++)       
      		for (k=0; k<N; k++)
        		matC[i][j] += matA[i][k] * matB[k][j];
    	}
  	}   /*** End of parallel region ***/

	printf("Done\n");
	end = clock();
    cpu_time = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("CPU Time = %f\n", cpu_time);
}