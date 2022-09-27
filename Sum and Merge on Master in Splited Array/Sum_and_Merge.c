#include <stdio.h>
#include <mpi.h>

int main(int argc , char **argv){
    int my_rank , nProc;

    MPI_Init(NULL,NULL);
    MPI_Comm_rank(MPI_COMM_WORLD,&my_rank);
    MPI_Comm_size(MPI_COMM_WORLD,&nProc);
    MPI_Status status;

    int array[] = {2,2,3,5,12,24,3,5,6,1000,7,20};
    int n = sizeof(array) / sizeof(int); // n = 12
    int section = n / (nProc-1), subArray[n];

    if(my_rank == 0){
        int ind = 0 , val , total = 0;
        for(int i = 1 ; i < nProc ; i++){
            MPI_Send(array+ind,section,MPI_INT,i,1,MPI_COMM_WORLD);
            ind = i * section;
        }

        for(int i = 1 ; i < nProc ; i++){
            MPI_Recv(&val,1,MPI_INT,MPI_ANY_SOURCE,MPI_ANY_TAG,MPI_COMM_WORLD,&status);
            total += val;
        }

        printf("Rank: %d and Total Sum = %d\n", my_rank, total);

    }
    else{
        MPI_Recv(&subArray,section,MPI_INT,MPI_ANY_SOURCE,MPI_ANY_TAG,MPI_COMM_WORLD,&status);

        int sum = 0;
        for(int i = 0 ; i < section ; i++){
            sum += subArray[i];
        }

        printf("Rank: %d and Sum = %d\n", my_rank, sum);
        MPI_Send(&sum,1,MPI_INT,0,1,MPI_COMM_WORLD);
    }
    return MPI_Finalize();
}