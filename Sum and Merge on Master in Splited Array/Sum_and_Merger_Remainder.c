#include <mpi.h>
#include <stdio.h>

int main(int argc , char **argv){

    int rank , section , i = 0 , x , n , nProc , sum , val;

    int a[] = {1,2,3,4,5,6,7,8,9,10};
    n = sizeof(a) / sizeof(int);
    int subArray[n];

    MPI_Init(NULL , NULL);
    MPI_Comm_rank(MPI_COMM_WORLD , &rank);
    MPI_Comm_size(MPI_COMM_WORLD , &nProc);
    MPI_Status status;


    if(rank == 0){
        int ind = 0, total = 0 , rem;
        ind = 0;
        section = n / (nProc - 1);
        rem = (n % (nProc - 1));

        for(i = 1 ; i < nProc; i++){

            x = (i <= rem)? section + 1 : section;
            MPI_Send(&x,1,MPI_INT,i,1,MPI_COMM_WORLD);
            MPI_Send(a+ind,x,MPI_INT , i , 1 , MPI_COMM_WORLD);
            ind += x;

        }

        for(i = 1 ; i < nProc ; i++){
            MPI_Recv(&val,1,MPI_INT,MPI_ANY_SOURCE,MPI_ANY_TAG,MPI_COMM_WORLD,&status);
            total += val;
        }

        printf("Summation from rank %d : %d\n",rank,total);

    }
    else{
        sum = 0;

        MPI_Recv(&x , 1 , MPI_INT , 0 , 1, MPI_COMM_WORLD , &status);
        MPI_Recv(&subArray , x , MPI_INT , 0 , 1, MPI_COMM_WORLD , &status);

        for(i = 0 ; i < x ; i++)
            sum += subArray[i];
        
        
        printf("Summation from rank %d : %d\n",rank,sum);

        MPI_Send(&sum,1,MPI_INT,0,1,MPI_COMM_WORLD); 
    }

    return MPI_Finalize();
}