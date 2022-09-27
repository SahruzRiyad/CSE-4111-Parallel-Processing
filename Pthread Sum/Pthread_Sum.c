//From Mehedi Hasan 
//To compile gcc fileName.c -o fileName -pthread
//To run ./fileName

#include <stdio.h>
#include<pthread.h>
#define MAX 16
#define TH 4

int ar[MAX], sum[TH], part;

void* array_sum(void* arg){
    int thread_id = part++;
    for(int i = thread_id*TH; i < (thread_id+1) * (MAX/TH); i++)
        sum[thread_id] += ar[i];
}

int main(){

    pthread_t thread[TH];
    int total = 0;

    for(int i = 0; i<MAX; i++){
        ar[i] = i+1;
        printf("%d ",ar[i]);
    }
    printf("\n");

    for(int i = 0; i<TH; i++)
        pthread_create(&thread[i], NULL, array_sum, (void*)NULL);

    for(int i = 0; i < TH; i++)
        pthread_join(thread[i],NULL);

    for(int i = 0 ; i< TH;i++){
        total += sum[i];
    }
    
    printf("Sum is %d\n",total);

    return 0;
}