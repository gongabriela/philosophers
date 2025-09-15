/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggoncalv <ggoncalv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 11:39:16 by ggoncalv          #+#    #+#             */
/*   Updated: 2025/09/15 19:13:14 by ggoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*server_routine(void *arg)
{
	t_monitor	*server;

	server = (t_monitor *)arg;
	wait_to_begin(server->philo);
	while (1)
	{
		if (check_death_all(server->philo) || finished_eating(server->philo))
			break ;
		usleep(100);
	}
	return (arg);
}

int	check_death_all(t_philos *philo)
{
	int	i;

	i = -1;
	while (++i < philo[0].number_of_philos)
	{
		pthread_mutex_lock(&philo[i].last_meal_mutex);
		pthread_mutex_lock(&philo[i].eating_mutex);
		if ((get_current_time() - philo[i].last_meal) >= philo[i].time_to_die
			&& philo[i].eating == false)
		{
			pthread_mutex_unlock(&philo[i].eating_mutex);
			pthread_mutex_unlock(&philo[i].last_meal_mutex);
			pthread_mutex_lock(philo->print_mutex);
			printf("%ld %d died\n", get_current_time()
				- philo->start_time, philo[i].id);
			pthread_mutex_unlock(philo->print_mutex);
			pthread_mutex_lock(philo[i].died_mutex);
			*(philo[i].died) = true;
			pthread_mutex_unlock(philo[i].died_mutex);
			return (1);
		}
		pthread_mutex_unlock(&philo[i].eating_mutex);
		pthread_mutex_unlock(&philo[i].last_meal_mutex);
	}
	return (0);
}

int	finished_eating(t_philos *philo)
{
	int	i;
	int	all_ate;

	i = -1;
	all_ate = 0;
	if (philo->must_eat == -1)
		return (0);
	while (++i < philo[0].number_of_philos)
	{
		pthread_mutex_lock(&philo[i].meals_eaten_mutex);
		if (philo[i].meals_eaten >= philo[i].must_eat)
			all_ate++;
		pthread_mutex_unlock(&philo[i].meals_eaten_mutex);
	}
	if (all_ate == philo[0].number_of_philos)
	{
		pthread_mutex_lock(philo->died_mutex);
		*(philo->died) = true;
		pthread_mutex_unlock(philo->died_mutex);
		return (1);
	}
	return (0);
}
