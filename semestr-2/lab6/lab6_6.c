#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 10

void *sleep_sort(void *arg){
    int n = *(int*)arg;
    sleep(n);
    printf("%d ", n);
    fflush(stdout);
    return NULL;
}

int main(){
    int arr[SIZE];
    pthread_t tid[SIZE];
    srand(time(NULL));
    printf("Исход массив:\n");
    for(int i=0; i<SIZE;i++){
        arr[i] = rand()%10;
        printf("%d ", arr[i]);
    }
    printf("\n");

    for(int i=0; i <SIZE;  i++){
        pthread_create(&tid[i], NULL, sleep_sort, &arr[i]);
    }

    printf("Отсорт массив:\n");
    for (int i=0; i <SIZE; i++){
        pthread_join(tid[i], NULL);

    }
    printf("\n");
}