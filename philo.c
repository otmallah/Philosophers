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
	int i;

	i = 0;
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
		pthread_mutex_unlock(&i->mutex[(a + 1) % i->holder[0]]);
		pthread_mutex_unlock(&i->mutex[a]);
		if (a == i->holder[0] - 1)
			a = 0;
	}
	//exit(0);
}

void    ft_creat_thread(char **tab, t_philo *philo)
{
	int     i;
	int     holder[3];

	philo->a = 0;
	philo->mutex = malloc(sizeof(pthread_mutex_t) * ft_atoi(tab[1]));
	while (i < ft_atoi(tab[1]))
	{
		pthread_mutex_init(&philo->mutex[i], NULL);
		i++;
	}
	i = 0;
	philo->philosophers = malloc(sizeof(pthread_t) *  ft_atoi(tab[1]));
	philo->holder[0] = ft_atoi(tab[1]);
	philo->holder[1] = ft_atoi(tab[2]);
	philo->holder[2] = ft_atoi(tab[3]);
	philo->holder[3] = ft_atoi(tab[4]);
	while (philo->a < ft_atoi(tab[1]))
	{
		pthread_create(&philo->philosophers[philo->a], NULL, fun, (void *)philo);
		usleep(100);
		philo->a++;
	}
	i = 0;
	while(++i < ft_atoi(tab[1]))
		pthread_join(philo->philosophers[i], NULL);
	i = 0;
	pthread_mutex_destroy(&philo->mutex[i]);
}

int main(int ac, char **av)
{
	t_philo philo;

	if (ac == 5)
	{
		if (checker_input_of_user(av) == 0)
			ft_creat_thread(av, &philo);
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