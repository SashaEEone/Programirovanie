#include <stdio.h>
#include <pthread.h>

void *thread_func(void *arg) {
    for (int i=1; i <=5; i++){
        printf("Дочерний поток: строка %d\n", i);
    }
    return NULL;
}

int main(){
    pthread_t tid;
    pthread_create(&tid, NULL, thread_func, NULL);
    pthread_join(tid, NULL);
    for (int i = 1; i <= 5; i++){
        printf("Родительский поток: строка %d\n", i);
    }
}
