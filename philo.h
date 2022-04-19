#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#define TRUE 1 

typedef struct s_philo {
    pthread_t       *philosophers;
    pthread_mutex_t *mutex;
    pthread_mutex_t lock;
    int             holder[4];
    int             a;
}   t_philo;
