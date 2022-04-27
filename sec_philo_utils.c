/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sec_philo_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otmallah <otmallah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 00:13:01 by otmallah          #+#    #+#             */
/*   Updated: 2022/04/27 00:24:54 by otmallah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	one_philo(char **tab)
{
	if (ft_atoi(tab[1]) == 1)
	{
		printf("\033[1;32m%ld philo 1 hase taken a fork\033[1;32m\n",
			get_current_time());
		ft_usleep(ft_atoi(tab[2]));
		printf("\033[1;31m%ld philo 1 is died\033[1;31m\n",
			get_current_time());
		return (1);
	}
	return (0);
}

long	get_current_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return (current_time.tv_sec * 1000 + current_time.tv_usec / 1000);
}

void	eats_some_spaghetti(t_philo *philo, int a)
{
	pthread_mutex_lock(&philo->sec_write.write);
	printf("\033[1;34m%ld philo %d is eating\033[1;34m\n",
		get_current_time(), a);
	philo->num_of_eat++;
	pthread_mutex_unlock(&philo->sec_write.write);
	ft_usleep(philo->holder[2]);
}

void	sleeping(t_philo *philo, int a)
{
	pthread_mutex_lock(&philo->sec_write.write);
	printf("\033[1;37m%ld philo %d is sleeping\033[1;37m\n",
		get_current_time(), a);
	pthread_mutex_unlock(&philo->sec_write.write);
	ft_usleep(philo->holder[3]);
}

int	checker_input_of_user(char **info_philo_tab)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	if (ft_strcmp(info_philo_tab[i], "-1") == 0
		|| ft_strcmp(info_philo_tab[i], "0") == 0)
	{
		write(2, "Really!!\n", 10);
		return (1);
	}
	else
	{
		if (checker(info_philo_tab) == 1)
			return (1);
	}
	return (0);
}
