/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otmallah <otmallah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 01:32:24 by otmallah          #+#    #+#             */
/*   Updated: 2022/04/27 01:13:34 by otmallah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*fun(void *times)
{
	t_philo	*philo;
	int		a;

	philo = times;
	a = philo->a;
	while (TRUE)
	{
		if (lock(philo, a) == 1)
			return (NULL);
	}
}

int	all_routine(t_philo **philo, char **tab)
{
	int	i;

	i = -1;
	norme(philo, tab);
	while (++i < ft_atoi(tab[1]))
	{
		philo[i]->a = i + 1;
		philo[i]->num_of_eat = 0;
		philo[i]->save_current_time = 0;
		if (pthread_create(&philo[i]->philosophers, NULL,
				fun, (void *)philo[i]) != 0)
			write(2, "Faild create thread\n", 20);
		usleep(100);
	}
	if (check_time_to_die(philo) == 1)
	{
		free(philo);
		return (1);
	}
	i = 0;
	while (i++ < ft_atoi(tab[1]))
		pthread_join(philo[i]->philosophers, NULL);
	return (0);
}

void	allocate(t_philo **philo, char **tab)
{
	int	i;

	i = 0;
	while (i < ft_atoi(tab[1]))
	{
		philo[i]->mutex = malloc(sizeof(pthread_mutex_t));
		pthread_mutex_init(philo[i]->mutex, NULL);
		pthread_mutex_init(&philo[i]->sec_mutex, NULL);
		pthread_mutex_init(&philo[i]->sec_write.write, NULL);
		i++;
	}
}

void	ft_creat_thread(char **tab)
{
	int		i;
	t_philo	**philo;

	if (one_philo(tab) == 1)
		return ;
	philo = malloc(sizeof(t_philo) * ft_atoi(tab[1]));
	i = -1;
	while (++i < ft_atoi(tab[1]))
	{
		philo[i] = malloc(sizeof(t_philo));
		philo[i]->holder[0] = ft_atoi(tab[1]);
		philo[i]->holder[1] = ft_atoi(tab[2]);
		philo[i]->holder[2] = ft_atoi(tab[3]);
		philo[i]->holder[3] = ft_atoi(tab[4]);
		if (tab[5])
			philo[i]->holder[4] = ft_atoi(tab[5]);
		else
			philo[i]->holder[4] = 0;
	}
	allocate(philo, tab);
	i = -1;
	if (all_routine(philo, tab) == 1)
		return ;
}

int	main(int ac, char **av)
{
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
