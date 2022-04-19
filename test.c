#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
  
pthread_t tid[2];
int counter;
pthread_mutex_t mutex;

void* trythis(void* arg)
{
    unsigned long i = 0;
    //pthread_mutex_lock(&);
    counter += 1;
    printf("\n Job %d has started\n", counter);
  
    for (i = 0; i < (0xFFFFFFFF); i++)
        ;
    printf("\n Job %d has finished\n", counter);
    pthread_mutex_unlock(&mutex);
    return NULL;
}
  
int main(void)
{
    int i = 0;
    int error;

    //pthread_mutex_init(&mutex, NULL);
    while (i < 2) {
        error = pthread_create(&(tid[i]), NULL, &trythis, NULL);
        if (error != 0)
            printf("\nThread can't be created : [%s]", strerror(error));
        i++;
    }
  
    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);
    //pthread_mutex_destroy(&mutex);

    return 0;
}