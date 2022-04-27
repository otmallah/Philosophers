/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otmallah <otmallah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 01:18:54 by otmallah          #+#    #+#             */
/*   Updated: 2022/04/27 00:46:34 by otmallah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (s1[i] - s2[i]);
}

long long int	ft_atoi(char *str)
{
	int			i;
	long long int r;

	i = 0;
	r = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		r = (str[i] - 48) + (r * 10);
		if (str[i + 1] < '0' || str[i + 1] > '9')
			return (r);
		i++;
	}
	return (0);
}

int	checker(char	**info_philo_tab)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (info_philo_tab[i])
	{
		while (info_philo_tab[i][j])
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
	return (0);
}

void	norme(t_philo **philo, char **tab)
{
	int	i;

	i = -1;
	while (++i < ft_atoi(tab[1]))
		philo[i]->next_fork = philo[(i + 1) % ft_atoi(tab[1])]->mutex;
}
