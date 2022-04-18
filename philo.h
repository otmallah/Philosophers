#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#define TRUE 1 

typedef struct s_philo {
    pthread_mutex_t mutex;
    pthread_t *philosophers;
    int     holder[3];
    int a;
}   t_philo;