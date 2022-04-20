#include "philo.h"

int a;
int x = 0;

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

void	eats_some_spaghetti(t_philo *philo, int a)
{
	printf("%d philo is eating\n", a);
	usleep(philo->holder[1] * 1000);
}

void	sleeping(t_philo *philo, int a)
{
	printf("%d philo is sleeping\n" , a);
	usleep(philo->holder[2] * 1000);
}

void		check_time_to_die(t_philo *philo, int a)
{
	if (philo->holder[2] + philo->holder[3] >= philo->holder[1])
	{
		printf("%d philo is died\n", a);
		exit(0);
	}
}


void    *fun(void *times)
{
	t_philo *i;
	int		a;
	int		result;

	i = (t_philo *)times;
	a = i->a;
	while (TRUE)
	{
		printf("%d philo is thinking\n", a);
		pthread_mutex_lock(&i->mutex[a]);
		printf("%d philo has taken a fork\n", a);
		pthread_mutex_lock(&i->mutex[(a + 1) % i->holder[0]]);
		eats_some_spaghetti(i, a);
		sleeping(i, a);
		check_time_to_die(i, a);
		pthread_mutex_unlock(&i->mutex[a]);
		pthread_mutex_unlock(&i->mutex[(a + 1) % i->holder[0]]);
	}

}

void    ft_creat_thread(char **tab, t_philo *philo)
{
	int     i;
	int     holder[3];

	philo->a = 0;
	philo->mutex = malloc(sizeof(pthread_mutex_t) * atoi(tab[1]));
	while (i < atoi(tab[1]))
	{
		pthread_mutex_init(&philo->mutex[i], NULL);
		i++;
	}
	i = 0;
	philo->philosophers = malloc(sizeof(pthread_t) *  atoi(tab[1]));
	philo->holder[0] = atoi(tab[1]);
	philo->holder[1] = atoi(tab[2]);
	philo->holder[2] = atoi(tab[3]);
	philo->holder[3] = atoi(tab[4]);
	while (philo->a < atoi(tab[1]))
	{
		pthread_create(&philo->philosophers[philo->a], NULL, fun, (void *)philo);
		usleep(100);
		philo->a++;
	}
	i = 0;
	while(++i < atoi(tab[1]))
		pthread_join(philo->philosophers[i], NULL);
	i = 0;
	pthread_mutex_destroy(&philo->mutex[i]);
}

int main(int ac, char **av)
{
	t_philo philo;

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