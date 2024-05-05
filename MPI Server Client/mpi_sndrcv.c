/*
	* Simple point-to-point communication implementation using MPI
	* One processor sends a message that is received by some other process exclusively.
*/

#include<stdio.h>
#include<mpi.h>

int main(int argc, char **argv) {
    
    int rank, size;
    char text[] = "Hello from processor 0", recv_text[25];
    char text1[] = "HI from processor 0";
    MPI_Status status;

    MPI_Init(&argc, &argv); //Initializes the MPI execution environment

    MPI_Comm_size(MPI_COMM_WORLD, &size); //Returns the total number of MPI processes in the specified communicator, such as MPI_COMM_WORLD

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);  //Returns the rank of the calling MPI process within the specified communicator

    //rank 0 processor sends message to rank 1 processor
    if(rank == 0){
        MPI_Send(text, 22, MPI_CHAR, 1, 100, MPI_COMM_WORLD);
	//MPI_Send(text1, 22, MPI_CHAR, 1, 101, MPI_COMM_WORLD);
        printf("Message sent from processor 0\n");
    }
    //rank 1 process receives the message
    else if(rank == 1){
        MPI_Recv(recv_text, 22, MPI_CHAR, 0, 100, MPI_COMM_WORLD, &status);
        printf("Message received by processor 1 : %s\n", recv_text);
    }

    MPI_Finalize(); //Terminates the MPI execution environment
    return 0;
}
