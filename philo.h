#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#define TRUE 1 

typedef struct s_philo {
    pthread_t       *philosophers;
    pthread_mutex_t *mutex;
    int             holder[4];
    int             a;
}   t_philo;


//utils 

int	ft_atoi(const char *str);
int	ft_strcmp(char *s1, char *s2);
