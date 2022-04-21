#include "philo.h"

long		get_current_time(void)
{
	struct timeval current_time;

	gettimeofday(&current_time, NULL);
	return (current_time.tv_sec * 1000 + current_time.tv_usec / 1000);
}

void	eats_some_spaghetti(t_philo *philo, int a)
{
	// philo->save_current_time = get_current_time();
	printf("%ld philo %d is eating\n", get_current_time(), a);
	usleep(philo->holder[1] * 1000);
}

void	sleeping(t_philo *philo, int a)
{
	printf("%ld philo %d is sleeping\n" , get_current_time(), a);
	usleep(philo->holder[2] * 1000);
}

void    *fun(void *arg)
{
	t_philo *philo;
	time_t	time;
	int		a;
	int		result;

	philo = arg;
	a = philo->a;
	while (TRUE)
	{
		pthread_mutex_lock(philo->mutex);
		printf("%ld ms philo %d has taken a fork\n", get_current_time(), a);
		pthread_mutex_lock(philo->next_fork);
		printf("%ld ms philo %d has taken next fork\n", get_current_time(), a);
		eats_some_spaghetti(philo, a);
		sleeping(philo, a);
		pthread_mutex_unlock(philo->mutex);
		pthread_mutex_unlock(philo->next_fork);
		printf("%ld philo %d is thinking\n", get_current_time(), a);
	}
}

int	main(int ac, char **av)
{
	t_philo *philo;
	int	i = 0;

	philo = malloc(sizeof(t_philo) * atoi(av[1]));
	while (i < ft_atoi(av[1]))
	{
		philo[i].holder[0] = ft_atoi(av[1]);
		philo[i].holder[1] = ft_atoi(av[2]);
		philo[i].holder[2] = ft_atoi(av[3]);
		philo[i].holder[3] = ft_atoi(av[4]);
		i++;
	}
	i = 0;
	while(i < atoi(av[1]))
	{
		philo[i].mutex = malloc(sizeof(pthread_mutex_t));
		i++;
	}
	i = 0;
	while (i < ft_atoi(av[1]))
	{
		philo[i].mutex = malloc(sizeof(pthread_mutex_t));
		philo[i].next_fork = malloc(sizeof(pthread_mutex_t));
		pthread_mutex_init(philo[i].mutex, NULL);
		i++;
	}
	i = 0;
	while (i < ft_atoi(av[1]))
	{
		philo[i].next_fork = philo[((i + 1) % ft_atoi(av[1]))].mutex;
		i++;
	}
	i = 0;
	while(i < atoi(av[1]))
	{
		pthread_mutex_init(philo[i].mutex, NULL);
		i++;
	}
	i = 0;
	while (i < atoi(av[1]))
	{
		philo->a = i + 1;
		pthread_create(&philo[i].philosophers, NULL, fun, (void *)philo);
		usleep(100);
		i++;
	}
	i = 0;
	while (i < atoi(av[1]))
	{
		pthread_join(philo[i].philosophers, NULL);
		i++;
	}
}