/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otmallah <otmallah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 01:48:16 by otmallah          #+#    #+#             */
/*   Updated: 2022/04/26 01:59:13 by otmallah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/time.h>
#define TRUE 1 

typedef struct s_write {
	pthread_mutex_t	write;
}	t_write;

typedef struct s_philo {
	pthread_t		philosophers;
	pthread_mutex_t	*mutex;
	pthread_mutex_t	*next_fork;
	pthread_mutex_t	sec_mutex;
	t_write			sec_write;
	long			save_current_time;
	int				num_of_eat;
	int				holder[5];
	int				a;
}	t_philo;

int		ft_atoi(const char *str);
int		ft_strcmp(char *s1, char *s2);
long	get_current_time(void);
void	ft_usleep(int time);

#endif