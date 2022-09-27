// -----------MPI----------
//To compile-  mpicc file_name.c -o file_name
//To run-  mpiexec -n number_of_process ./file_name
//To avoid warning-  mpiexec -quiet -n number_of_process ./file_name

#include <mpi.h>
#include <stdio.h>

int main(int argc , char **argv){
    int my_rank , nProc;

    MPI_Init(NULL,NULL);
    MPI_Comm_rank(MPI_COMM_WORLD , &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &nProc);

    printf("Number of Process: %d and Rank: %d\n",nProc,my_rank);
}
