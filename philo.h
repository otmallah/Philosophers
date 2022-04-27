/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otmallah <otmallah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 01:48:16 by otmallah          #+#    #+#             */
/*   Updated: 2022/04/27 01:10:27 by otmallah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# define TRUE 1 

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

long long int	ft_atoi(char *str);
int		ft_strcmp(char *s1, char *s2);
long	get_current_time(void);
void	ft_usleep(int time);
int		checker_input_of_user(char **info_philo_tab);
void	sleeping(t_philo *philo, int a);
void	eats_some_spaghetti(t_philo *philo, int a);
long	get_current_time(void);
int		one_philo(char **tab);
int		checker(char	**info_philo_tab);
void	norme(t_philo **philo, char **tab);
int		lock(t_philo *philo, int a);
int		sec_che(t_philo **philo);
int		check_time_to_die(t_philo **philo);
#endif
