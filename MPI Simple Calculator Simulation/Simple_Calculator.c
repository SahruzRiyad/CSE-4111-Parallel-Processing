#include <stdio.h>
#include <mpi.h>

int main(int argc , char **argv){
    int my_rank , a = 4 , b = 2;

    MPI_Init(NULL,NULL);
    MPI_Comm_rank(MPI_COMM_WORLD,&my_rank);

    if(my_rank == 0)
        printf("Rank: %d and Sum(a+b) = %d\n",my_rank,a+b);
    else if(my_rank == 1)
        printf("Rank: %d and Sub(a-b) = %d\n",my_rank,a-b);
    else if(my_rank == 2)
        printf("Rank: %d and Mul(a*b) = %d\n",my_rank,a*b);
    else if(my_rank == 3)
        printf("Rank: %d and Div(a/b) = %d\n",my_rank,a/b);
    
    return MPI_Finalize();
}