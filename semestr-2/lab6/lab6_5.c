#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void cleanup(void *arg){
    char **strok=arg;
    printf("Поток %s завершился\n", *strok);
}

void *print_strok(void *arg){
    char **strok= arg;
    pthread_cleanup_push(cleanup, arg);
    while(1){
        for (int i = 0; i<3; i++){
            printf("%s ", strok[i]);
        }
        printf("\n");
        sleep(1);
    }   
    pthread_cleanup_pop(0);
    return NULL;
}

int main(){
    pthread_t tid[4];
    char *one[]= {"red", "blue", "green"};
    char *two[]= {"bmw", "mrs", "por"};
    char *three[]= {"men", "woomen", "child"};
    char *four[]= {"one", "two", "three"};

    char **fool[]={one, two, three, four};

    for (int i = 0; i<4; i++){
        pthread_create(&tid[i], NULL, print_strok, fool[i]);
    }
    sleep(2);
    for (int i = 0; i<4; i++){
        pthread_cancel(tid[i]);
        pthread_join(tid[i], NULL);
    }
}
