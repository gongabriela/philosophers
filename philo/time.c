/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggoncalv <ggoncalv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 13:46:40 by ggoncalv          #+#    #+#             */
/*   Updated: 2025/09/15 16:39:16 by ggoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_usleep(long time_in_ms, t_philos *philo)
{
	long	start_time;
	long	current_time;

	start_time = get_current_time();
	while (check_death(philo) == false)
	{
		current_time = get_current_time();
		if (current_time - start_time >= time_in_ms)
			break ;
		usleep(100);
	}
}

long	get_current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	get_start_time(t_philos *philo)
{
	int		i;
	long	start_time;

	start_time = get_current_time();
	i = -1;
	while (++i < philo[0].number_of_philos)
	{
		philo[i].start_time = start_time;
		philo[i].last_meal = start_time;
	}
}
