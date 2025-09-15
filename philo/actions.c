/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggoncalv <ggoncalv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 12:02:57 by ggoncalv          #+#    #+#             */
/*   Updated: 2025/09/15 18:46:12 by ggoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	grab_forks(t_philos *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		print_msg("has taken a fork", philo);
		if (check_death(philo) == true)
			return (pthread_mutex_unlock(philo->right_fork), 1);
		pthread_mutex_lock(philo->left_fork);
		print_msg("has taken a fork", philo);
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		print_msg("has taken a fork", philo);
		if (check_death(philo) == true)
			return (pthread_mutex_unlock(philo->left_fork), 1);
		pthread_mutex_lock(philo->right_fork);
		print_msg("has taken a fork", philo);
	}
	return (0);
}

int	eat(t_philos *philo)
{
	if (check_death(philo) == true)
		return (pthread_mutex_unlock(philo->left_fork),
			pthread_mutex_unlock(philo->right_fork), 1);
	pthread_mutex_lock(&philo->eating_mutex);
	philo->eating = true;
	pthread_mutex_unlock(&philo->eating_mutex);
	print_msg("is eating", philo);
	pthread_mutex_lock(&philo->last_meal_mutex);
	philo->last_meal = get_current_time();
	pthread_mutex_unlock(&philo->last_meal_mutex);
	pthread_mutex_lock(&philo->meals_eaten_mutex);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meals_eaten_mutex);
	ft_usleep(philo->time_to_eat, philo);
	pthread_mutex_lock(&philo->eating_mutex);
	philo->eating = false;
	pthread_mutex_unlock(&philo->eating_mutex);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	return (0);
}

void	ft_sleep(t_philos *philo)
{
	if (check_death(philo) == true)
		return ;
	print_msg("is sleeping", philo);
	ft_usleep(philo->time_to_sleep, philo);
}

void	think(t_philos *philo)
{
	if (check_death(philo) == true)
		return ;
	print_msg("is thinking", philo);
	if (philo->number_of_philos % 2 == 1)
		usleep(1000);
}
