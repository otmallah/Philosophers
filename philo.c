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

void	eats_some_spaghetti(t_philo *philo, int a)
{
	philo->num_of_eat++;
	//printf("num %d\n", philo->num_of_eat);
	pthread_mutex_lock(&philo->write);
	printf("%ld philo %d is eating\n", get_current_time(), a);
	pthread_mutex_unlock(&philo->write);
	ft_usleep(philo->holder[2]);
}

void	sleeping(t_philo *philo, int a)
{
	pthread_mutex_lock(&philo->write);
	printf("%ld philo %d is sleeping\n" , get_current_time(), a);
	pthread_mutex_unlock(&philo->write);
	ft_usleep(philo->holder[3]);
}

int	check_time_to_die(t_philo **philo)
{
	int i;
	int a;
	int time;

	i = 0;
	a = philo[i]->holder[0];
	time = philo[i]->holder[1];
	int save;
	while (TRUE)
	{
		while (i < a)
		{
			pthread_mutex_lock(&philo[i]->write);
			save = get_current_time() - philo[i]->save_current_time;
			if (philo[i]->save_current_time != 0 && save > time )
			{
				printf("%ld philo %d died\n", get_current_time(), i);
				return 1;
			}
			pthread_mutex_unlock(&philo[i]->write);
			i++;
		}
		i = 0;
	}
	return 0;
}

// int		number_of_eat(t_philo **philo)
// {
// 	int i;
// 	int size;
// 	int count = 0;
// 	int	num;

// 	i = 0;
// 	size = philo[i]->holder[0];
// 	num = philo[i]->holder[4];
// 	printf("%d \n", size);
// 	printf("%d \n", num);
// 	puts("*-*-*-*-*-*-*-*--*-*-**--*-*-*-*-*-*");
// 	while (TRUE)

// 	while (i < size)
// 	{
// 		count = count + philo[i]->num_of_eat;
// 		printf("count = %d\n", philo[i]->num_of_eat);
// 		if (count == (size * num))
// 		{
// 			puts("hna");
// 			exit(0);
// 			break;
// 		}
// 		i++;
// 	}
// 	return 0;
// }

void    *fun(void *times)
{
	t_philo *philo;
	int		a;
	int		result;

	philo = times;
	a = philo->a;
	while (TRUE)
	{
		pthread_mutex_lock(&philo->write);
		// if (philo->save_current_time && philo->holder[1] < get_current_time() - philo->save_current_time)
		// 	return (NULL);
		pthread_mutex_lock(philo->mutex);
		printf("%ld ms philo %d has taken a fork\n", get_current_time(), a);
		pthread_mutex_unlock(&philo->write);
		pthread_mutex_lock(philo->next_fork);
		pthread_mutex_lock(&philo->write);
		printf("%ld ms philo %d has taken next fork\n", get_current_time(), a);
		pthread_mutex_unlock(&philo->write);
		philo->save_current_time = get_current_time();
		eats_some_spaghetti(philo, a);
		pthread_mutex_unlock(philo->mutex);
		pthread_mutex_unlock(philo->next_fork);
		sleeping(philo, a);
		pthread_mutex_lock(&philo->write);
		printf("%ld ms philo %d put down the fork\n", get_current_time(), a);
		pthread_mutex_unlock(&philo->write);
		pthread_mutex_lock(&philo->write);
		printf("%ld philo %d is thinking\n", get_current_time(), a);
		pthread_mutex_unlock(&philo->write);
	}
}


int		one_philo(char **tab)
{
	printf("%ld philo 1 hase taken a fork \n", get_current_time());
	ft_usleep(ft_atoi(tab[1]));
	printf("%ld philo 1 is died", get_current_time());
	return 1;
}

void 	ft_creat_thread(char **tab)
{
	int		i;
	t_philo	**philo;

	if (ft_atoi(tab[1]) == 1)
	{
		if (one_philo(tab) == 1)
			return ;
	}
	philo = malloc(sizeof(t_philo) * ft_atoi(tab[1]));
	i = 0;
	while (i < ft_atoi(tab[1]))
	{
		philo[i] = malloc(sizeof(t_philo));
		philo[i]->holder[0] = ft_atoi(tab[1]);
		philo[i]->holder[1] = ft_atoi(tab[2]);
		philo[i]->holder[2] = ft_atoi(tab[3]);
		philo[i]->holder[3] = ft_atoi(tab[4]);
		philo[i]->num_of_eat = 0;
		if (tab[5])
			philo[i]->holder[4] = ft_atoi(tab[5]);
		i++;
	}
	i = 0;
	while (i < ft_atoi(tab[1]))
	{
		philo[i]->mutex = malloc(sizeof(pthread_mutex_t));
		philo[i]->next_fork = malloc(sizeof(pthread_mutex_t));
		pthread_mutex_init(philo[i]->mutex, NULL);
		pthread_mutex_init(&philo[i]->write, NULL);
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
		philo[i]->save_current_time = 0;
		pthread_create(&philo[i]->philosophers, NULL, fun, (void *)philo[i]);
		usleep(100);
		i++;
	}
	// if (tab[5])
	// {
	// 	if (number_of_eat(philo) == 1)
	// 	{
	// 		return ;
	// 	}
	// }
	if (check_time_to_die(philo) == 1)
	{
		//puts("hana");
		return ;
	}
	i = 0;
	while(i++ < ft_atoi(tab[1]))
		pthread_join(philo[i]->philosophers, NULL);
	// i = 0;
	while (i++ < ft_atoi(tab[1]))
		pthread_mutex_destroy(philo[i]->mutex);
	//return 0;
}


int main(int ac, char **av)
{
	t_philo philo;

	if (ac == 5 || ac == 6)
	{
		if (checker_input_of_user(av) == 0)
		{
			ft_creat_thread(av);
		}
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