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

static long	ft_check(const char *str, int i, int n)
{
	long	number;
	long	help;

	number = 0;
	help = 0;
	while (str[n] >= '0' && str[n] <= '9')
	{
		help = 10 * help + (str[n] - '0');
		if (i == -1)
		{
			if ((help / 10) != number)
				return (0);
		}
		if (i == 1)
		{
			if ((help / 10) != number)
				return (-1);
		}
		number = 10 * number + (str[n] - '0');
		n++;
	}
	return (number * i);
}

int	ft_atoi(const char *str)
{
	long	number;
	int		sign;
	int		n;

	number = 0;
	sign = 1;
	n = 0;
	while (str[n] == '\f' || str[n] == '\n' || str[n] == 32
		|| str[n] == '\r' || str[n] == '\v' || str[n] == '\t')
		n++;
	if (str[n] == '-')
	{
		sign *= -1;
		n++;
	}
	else if (str[n] == '+')
		n++;
	number = ft_check(str, sign, n);
	return (number);
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
