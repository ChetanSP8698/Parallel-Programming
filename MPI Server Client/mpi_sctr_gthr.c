/*Implementing Collective Communication using MPI Scatter and Gather functions
  u is an array initialized by the master processor i.e. rank = 0,
  used size of array after scatter for every processor as 2, i.e. after scatter every processor will have an array of size 2,
  after scatter every processor adds the value of its rank in each of its elements,
  Output can be checked to make sure proper changes are made and that scatter - gather has been executed properly
*/

#include<stdio.h>
#include<mpi.h>
#include<stdlib.h>

int main(int argc, char *argv[]){
    int size, rank, u[100], v[3];
    MPI_Init(&argc, &argv);
    
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    //Master initializing array u[]
    if(rank == 0){
        printf("Master Scattering : ");
        for(int i = 0; i < size * 2; i++){
            u[i] = i + 1;
            printf("%d ", u[i]);
        }
    }
    printf("\n");
    //Scattering elements
    MPI_Scatter(u, 2, MPI_INT, v, 2, MPI_INT, 0, MPI_COMM_WORLD);

    //Unique additions to the elements by each processor
    for(int i = 0; i < 2; i++){
        v[i] *= rank;
    }
    
    //Consolidating the elements back into u[]
    MPI_Gather(v, 2, MPI_INT, u, 2, MPI_INT, 0, MPI_COMM_WORLD);

    //Parent prints the contents of u[] to reflect the changes
    if(rank == 0){
        for(int i = 0; i < size; i++){
	    printf("\nProcessor %d calculated values : ", i);
            for(int j = 0; j < 2; j++){
                int k = i * 2 + j;
                printf("%d ", u[k]);
            }
        }
	printf("\n");
    }
    fflush(stdout); 

    MPI_Finalize();
    return 0;
}
