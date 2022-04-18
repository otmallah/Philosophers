#include "philo.h"

void    checker_input_of_user(char **info_philo_tab)
{
	int i;
	int j;

	i = 1;
	j = 0;
	while (info_philo_tab[i])
	{
		while(info_philo_tab[i][j])
		{
			if (info_philo_tab[i][j] >= '0' && info_philo_tab[i][j] <= '9')
				j++;
			else
			{
				write (2, "ERROR :Only num\n", 17);
				exit(0) ;
			}
		}
		j = 0;
		i++;
	}
}

void    *fun(void *times)
{
	t_philo i;
	int		result;

	i = *(t_philo *)times;
	while (TRUE)
	{
		pthread_mutex_lock(&i.mutex);
		printf("time to sleep = %d\n", i.holder[2]);
		printf("time to eats = %d\n", i.holder[1]);
		printf("time to die = %d\n", i.holder[0]);
		pthread_mutex_unlock(&i.mutex);
		usleep(1000000);
	}
}

void    ft_creat_thread(char **tab, t_philo *philo)
{
	int     i;
	int     holder[3];

	i = 0;
	pthread_mutex_init(&philo->mutex, NULL);
	philo->philosophers = malloc(sizeof(pthread_t) *  atoi(tab[1]));
	philo->holder[0] = atoi(tab[2]);
	philo->holder[1] = atoi(tab[3]);
	philo->holder[2] = atoi(tab[4]);
	while (i < atoi(tab[1]))
	{
		pthread_create(&philo->philosophers[i], NULL, fun, (void *)philo);
		pthread_join(philo->philosophers[i], NULL);
		i++;
	}
	pthread_mutex_destroy(&philo->mutex);
}

int main(int ac, char **av)
{
	t_philo philo;

	philo.a = 5 ;
	if (ac == 5)
	{
		checker_input_of_user(av);
		ft_creat_thread(av, &philo);
	}
	else
	{
		if (ac > 5)
			write(2, "ERROR :Enter just 4 arg\n", 25);
		else
			write(2, "ERROR :Need more\n", 18);
	}
}