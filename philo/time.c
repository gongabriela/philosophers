/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggoncalv <ggoncalv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 10:45:27 by ggoncalv          #+#    #+#             */
/*   Updated: 2025/09/10 10:45:27 by ggoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/philosophers.h"

void	get_start_time(t_struct *dinner, t_monitor *server)
{
	struct timeval	start_time;
	int	i;

	gettimeofday(&start_time, NULL);
	i = 0;
	while (i < dinner[0].number_of_philos)
	{
		dinner[i].start_time = start_time;
		dinner[i].last_meal = 0;
		i++;
	}
	server->start_time = start_time;
}

void	get_start_time_in_ms(t_struct *dinner)
{
	long	start_time_ms;

	start_time_ms = dinner->start_time.tv_sec * 1000 + dinner->start_time.tv_usec / 1000;
	dinner->last_meal = start_time_ms;
}

void	get_current_time(t_struct *dinner)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	dinner->current_time = current_time;
}

void	get_timestamp(t_struct *dinner)
{
	long	seconds;
	long	useconds;
	long	timestamp;

	get_current_time(dinner);
	seconds = dinner->current_time.tv_sec - dinner->start_time.tv_sec;
	useconds = dinner->current_time.tv_usec - dinner->start_time.tv_usec;
	timestamp = seconds * 1000 + useconds / 1000;
	dinner->timestamp = timestamp;
}
