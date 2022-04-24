#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/time.h>
#define TRUE 1 

typedef struct s_philo {
	pthread_t       philosophers;
	pthread_mutex_t *mutex;
	pthread_mutex_t write;
	pthread_mutex_t *next_fork;
	int				save_current_time;
	int				num_of_eat;
	int             holder[5];
	int             a;
}   t_philo;

int     ft_atoi(const char *str);
int     ft_strcmp(char *s1, char *s2);
long    get_current_time(void);
void    ft_usleep(int time);