/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_usleep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otmallah <otmallah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 02:31:31 by otmallah          #+#    #+#             */
/*   Updated: 2022/04/24 00:31:24 by otmallah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    ft_usleep(int time)
{
    long    save_time;

    save_time = get_current_time() + time;
    while (get_current_time() < save_time)
        usleep(100);
}