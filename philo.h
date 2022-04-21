#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/time.h>
#define TRUE 1 

typedef struct s_philo {
    pthread_t       philosophers;
    pthread_mutex_t *mutex;
    long      save_current_time;
    long      save_old_time;
    int             holder[4];
    pthread_mutex_t *fork;
    pthread_mutex_t *next_fork;
    int             a;
}   t_philo;


//utils 

int	ft_atoi(const char *str);
int	ft_strcmp(char *s1, char *s2);
