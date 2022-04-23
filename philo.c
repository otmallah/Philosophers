#include "philo.h"

int a;
int x = 0;

int		checker_input_of_user(char **info_philo_tab)
{
	int i;
	int j;

	i = 1;
	j = 0;
	if (ft_strcmp(info_philo_tab[i], "-1") == 0 || ft_strcmp(info_philo_tab[i], "0") == 0)
	{
		write(2, "Really!!\n", 10);
		return (1);
	}
	else
	{
		while (info_philo_tab[i])
		{
			while(info_philo_tab[i][j])
			{
				if (info_philo_tab[i][j] >= '0' && info_philo_tab[i][j] <= '9')
					j++;
				else
				{
					write (2, "ERROR :Only integer num\n", 25);
					return (1);
				}
			}
			j = 0;
			i++;
		}
	}
	return (0);
}

long		get_current_time(void)
{
	struct timeval current_time;

	gettimeofday(&current_time, NULL);
	return (current_time.tv_sec * 1000 + current_time.tv_usec / 1000);
}

int		number_of_eat(t_philo **philo)
{
	int i;
	int size;
	int count = 0;

	i = 0;
	size = philo[i]->holder[0];
	//puts("*-*-*-*-*-*-*-*--*-*-**--*-*-*-*-*-*");
	while (TRUE)
	{
		while (i < size)
		{
			if (philo[i]->num_of_eat == philo[i]->num_of_eat)
			{
					return 1;
			}
			i++;
		}
		i = 0;
	}
	return 0;
}

void	eats_some_spaghetti(t_philo *philo, int a)
{
	// philo->save_current_time = get_current_time();
	philo->num_of_eat++;
	//printf("nuuum == %d\n", philo->num_of_eat);
	printf("%ld philo %d is eating\n", get_current_time(), a);
	usleep(philo->holder[4] * 1000);
}

void	sleeping(t_philo *philo, int a)
{
	printf("%ld philo %d is sleeping\n" , get_current_time(), a);
	usleep(philo->holder[3] * 1000);
}

int		check_time_to_die(t_philo **philo)
{
	int i;
	int a;
	int time;
	int save;

	i = 0;
	a = philo[i]->holder[0];
	time = philo[i]->holder[1];
	while (TRUE)
	{
		while (i < a)
		{
			save = get_current_time() - philo[i]->save_current_time ;
			if (save > time)
			{
				//printf("num %d\n", save);
				printf("%ld philo %d died\n", get_current_time(), i);
				return 1;
			}
			i++;
		}
		i = 0;
	}
	return 0;
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
		pthread_mutex_unlock(philo->mutex);
		printf("%ld ms philo %d has put down right fork\n", get_current_time(), a);
		pthread_mutex_unlock(philo->next_fork);
		printf("%ld ms philo %d has put down left fork\n", get_current_time(), a);
		sleeping(philo, a);
		philo->save_current_time = get_current_time();
		printf("%ld philo %d is thinking\n", get_current_time(), a);
	}
}

int		check_time_to_die_philo(t_philo *philo)
{
	int a;

	a = philo->a;
	if (philo->holder[2] + philo->holder[3] >= philo->holder[1])
	{
		printf("%ld ms philo %d is die\n", get_current_time(), a);
		return 1;
	}
	return 0;
}

int		one_philo(char **tab)
{
	t_philo *philo;

	printf("%ld philo 1 has taken a fork \n", get_current_time());
	usleep(atoi(tab[2]) * 1000);
	usleep(atoi(tab[3]) * 1000);
	printf("%ld philo 1 is died \n", get_current_time());
	return 1;
}

void		ft_creat_thread(char **tab)
{
	int     i;
	t_philo **philo;

	if (ft_atoi(tab[1]) == 1)
	{
		if (one_philo(tab) == 1)
			return ;
	}
	i = 0;
	philo = malloc(sizeof(t_philo) * ft_atoi(tab[1]));
	while (i < ft_atoi(tab[1]))
	{
		philo[i] = malloc(sizeof(t_philo));
		philo[i]->holder[0] = ft_atoi(tab[1]);
		philo[i]->holder[1] = ft_atoi(tab[2]);
		philo[i]->holder[2] = ft_atoi(tab[3]);
		philo[i]->holder[3] = ft_atoi(tab[4]);
		if (tab[5])
			philo[i]->holder[4] = ft_atoi(tab[5]);
		i++;
	}
	i = 0;
	while (i < ft_atoi(tab[1]))
	{
		philo[i]->mutex = malloc(sizeof(pthread_mutex_t *));
		philo[i]->next_fork = malloc(sizeof(pthread_mutex_t *));
		pthread_mutex_init(philo[i]->mutex, NULL);
		i++;
	}
	i = 1;
	while (i < ft_atoi(tab[1]))
	{
		philo[i]->next_fork = philo[(i + 1) % ft_atoi(tab[1])]->mutex;
		i++;
	}
	i = 0;
	while (i < ft_atoi(tab[1]))
	{
		philo[i]->a = i + 1;
		philo[i]->save_current_time = get_current_time();
		pthread_create(&philo[i]->philosophers, NULL, fun, (void *)philo[i]);
		usleep(100);
		i++;
	}
	i = 0;
	if (tab[5])
	{
		if (number_of_eat(philo) == 1)
		{
			return ;
		}
	}
	while(++i < ft_atoi(tab[1]))
		pthread_join(philo[i]->philosophers, NULL);
	i = 0;
	while (++i < ft_atoi(tab[1]))
		pthread_mutex_destroy(philo[i]->mutex);
}


int main(int ac, char **av)
{
	t_philo philo;

	if (ac == 6 || ac == 5)
	{
		if (checker_input_of_user(av) == 0)
			ft_creat_thread(av);
	}
	else
	{
		if (ac > 5)
			write(2, "ERROR :Enter just 4 arg\n", 25);
		else
			write(2, "ERROR :Need more\n", 18);
	}
	return (0);
}