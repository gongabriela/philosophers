/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggoncalv <ggoncalv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 13:43:58 by ggoncalv          #+#    #+#             */
/*   Updated: 2025/09/15 18:32:02 by ggoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*philo_routine(void *arg)
{
	t_philos	*philo;

	philo = (t_philos *)arg;
	wait_to_begin(philo);
	if (philo->id % 2 == 0)
		ft_usleep(philo->time_to_eat / 2, philo);
	if (philo->number_of_philos == 1)
	{
		table_for_one(philo);
		return (arg);
	}
	while (check_death(philo) == false)
	{
		if (grab_forks(philo) == 1)
			break ;
		if (eat(philo) == 1)
			break ;
		ft_sleep(philo);
		think(philo);
	}
	return (arg);
}

void	wait_to_begin(t_philos *philo)
{
	while (1)
	{
		pthread_mutex_lock(philo->begin_mutex);
		if (*(philo->begin) == true)
		{
			pthread_mutex_unlock(philo->begin_mutex);
			break ;
		}
		pthread_mutex_unlock(philo->begin_mutex);
		usleep(100);
	}
}

void	table_for_one(t_philos *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_msg("has taken a fork", philo);
	while (check_death(philo) == false)
		usleep(100);
	pthread_mutex_unlock(philo->left_fork);
}

bool	check_death(t_philos *philo)
{
	bool	check_death;

	pthread_mutex_lock(philo->died_mutex);
	check_death = *(philo->died);
	pthread_mutex_unlock(philo->died_mutex);
	return (check_death);
}
