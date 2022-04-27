/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_usleep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otmallah <otmallah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 02:31:31 by otmallah          #+#    #+#             */
/*   Updated: 2022/04/27 01:11:04 by otmallah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep(int time)
{
	long	save_time;

	save_time = get_current_time() + time;
	while (get_current_time() <= save_time)
		usleep(100);
}

int	lock(t_philo *philo, int a)
{
	pthread_mutex_lock(&philo->sec_mutex);
	if (philo->save_current_time
		&& philo->holder[1] < get_current_time() - philo->save_current_time)
		return (1);
	pthread_mutex_unlock(&philo->sec_mutex);
	pthread_mutex_lock(philo->mutex);
	pthread_mutex_lock(&philo->sec_write.write);
	printf("%ld ms philo %d has taken a fork\n", get_current_time(), a);
	pthread_mutex_unlock(&philo->sec_write.write);
	pthread_mutex_lock(philo->next_fork);
	pthread_mutex_lock(&philo->sec_write.write);
	printf("%ld ms philo %d has taken next fork\n", get_current_time(), a);
	pthread_mutex_unlock(&philo->sec_write.write);
	pthread_mutex_lock(&philo->sec_mutex);
	philo->save_current_time = get_current_time();
	pthread_mutex_unlock(&philo->sec_mutex);
	eats_some_spaghetti(philo, a);
	pthread_mutex_unlock(philo->mutex);
	pthread_mutex_unlock(philo->next_fork);
	sleeping(philo, a);
	pthread_mutex_lock(&philo->sec_write.write);
	printf("%ld philo %d is thinking\n", get_current_time(), a);
	pthread_mutex_unlock(&philo->sec_write.write);
	return (0);
}

int	sec_che(t_philo **philo)
{
	int	i;
	int	save;

	i = -1;
	while (++i < philo[0]->holder[0])
	{
		pthread_mutex_lock(&philo[i]->sec_write.write);
		save = get_current_time() - philo[i]->save_current_time;
		pthread_mutex_unlock(&philo[i]->sec_write.write);
		if (philo[i]->save_current_time != 0 && save > philo[0]->holder[1])
		{
			pthread_mutex_lock(&philo[i]->sec_write.write);
			printf("\033[1;31m%ld philo %d died\033[1;31m\n",
				get_current_time(), philo[i]->a);
			return (1);
		}
		if (philo[0]->holder[4] != 0
			&& philo[i]->num_of_eat > philo[0]->holder[4])
		{
			pthread_mutex_lock(&philo[i]->sec_mutex);
			printf("%ld all philosophers has eaten\n", get_current_time());
			return (1);
		}
	}
	return (0);
}

int	check_time_to_die(t_philo **philo)
{
	while (TRUE)
	{
		if (sec_che(philo) == 1)
			return (1);
	}
	return (0);
}
