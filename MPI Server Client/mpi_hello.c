#include <stdio.h>
#include <mpi.h>
     
int main(int argc, char **argv) {
      	int size, rank, version, subversion;

      	MPI_Init(&argc, &argv);

      	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
      	MPI_Comm_size(MPI_COMM_WORLD, &size);
      	MPI_Get_version(&version,&subversion);
      
	printf("Hello world! I'm process %i out of %i processes\n", rank, size);
      	printf("Version : %i\nSubversion : %i\n", version, subversion);
	MPI_Finalize();
      return 0;
}
