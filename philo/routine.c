/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggoncalv <ggoncalv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 18:07:34 by ggoncalv          #+#    #+#             */
/*   Updated: 2025/09/09 18:07:34 by ggoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/philosophers.h"

void	*routine(void *arg)
{
	t_struct	*dinner;

	dinner = (t_struct *)arg;
	//get_start_time_in_ms(dinner);
	if (dinner->number_of_philos == 1)
	{
		exec_single_philo(dinner);
		return (NULL);
	}
	if (dinner->philo_id % 2 == 0)
		think(dinner, dinner->time_to_eat);
	while (1)
	{
		if (get_death_info_dinner(dinner) == true)
			break ;
		grab_forks(dinner);
		eat(dinner, dinner->time_to_eat);
		if (meals_eaten_check(dinner))
			return (NULL);
		ft_sleep(dinner, dinner->time_to_sleep);
		if (get_death_info_dinner(dinner) == true)
			break ;
		think(dinner, 6);
	}
	return (NULL);
}

int	meals_eaten_check(t_struct *dinner)
{
	if (dinner->must_eat == -1)
		return (0);
	dinner->meals_eaten++;
	if (dinner->must_eat == dinner->meals_eaten)
	{
		pthread_mutex_lock(&dinner->finished_mutex);
		dinner->finished = 1;
		pthread_mutex_unlock(&dinner->finished_mutex);
		return (1);
	}
	return (0);
}

void	exec_single_philo(t_struct *dinner)
{
	pthread_mutex_t *fork;
	if (dinner->left_fork)
		fork = dinner->left_fork;
	else
		fork = dinner->right_fork;
	pthread_mutex_lock(fork);
	pthread_mutex_lock(dinner->print_mutex);
	get_timestamp(dinner);
	printf("%ld %d has taken a fork\n", dinner->timestamp, dinner->philo_id);
	pthread_mutex_unlock(dinner->print_mutex);
	usleep(dinner->time_to_die * 1000);
	pthread_mutex_unlock(fork);
}

void	think(t_struct *dinner, int	ms)
{
	get_timestamp(dinner);
	pthread_mutex_lock(dinner->print_mutex);
	printf("%ld %d is thinking\n", dinner->timestamp, dinner->philo_id);
	pthread_mutex_unlock(dinner->print_mutex);
	usleep(ms * 1000);
}

void	grab_forks(t_struct *dinner)
{
	pthread_mutex_t	*fork_1;
	pthread_mutex_t	*fork_2;

	if (dinner->philo_id % 2 == 0)
	{
		fork_1 = dinner->left_fork;
		fork_2 = dinner->right_fork;
	}
	else
	{
		fork_1 = dinner->right_fork;
		fork_2 = dinner->left_fork;
	}
	pthread_mutex_lock(fork_1);

	get_timestamp(dinner);
	pthread_mutex_lock(dinner->print_mutex);
	if (get_death_info_dinner(dinner) == true)
	{
		pthread_mutex_unlock(dinner->print_mutex);
		pthread_mutex_unlock(fork_1);
		return ;
	}
	printf("%ld %d has taken a fork\n", dinner->timestamp, dinner->philo_id);
	pthread_mutex_unlock(dinner->print_mutex);

	if (get_death_info_dinner(dinner) == true)
	{
		pthread_mutex_unlock(fork_1);
		return ;
	}

	pthread_mutex_lock(fork_2);
	get_timestamp(dinner);
	pthread_mutex_lock(dinner->print_mutex);
	printf("%ld %d has taken a fork\n", dinner->timestamp, dinner->philo_id);
	pthread_mutex_unlock(dinner->print_mutex);
}

void	eat(t_struct *dinner, int ms)
{
	if (get_death_info_dinner(dinner) == true)
	{
		pthread_mutex_unlock(dinner->left_fork);
		pthread_mutex_unlock(dinner->right_fork);
		return ;
	}
	get_timestamp(dinner);
	update_last_meal(dinner);
	pthread_mutex_lock(dinner->print_mutex);
	printf("%ld %d is eating\n", dinner->timestamp, dinner->philo_id);
	pthread_mutex_unlock(dinner->print_mutex);
	usleep(ms * 1000);
	pthread_mutex_unlock(dinner->left_fork);
	pthread_mutex_unlock(dinner->right_fork);
}

void	ft_sleep(t_struct *dinner, int ms)
{
	if (get_death_info_dinner(dinner) == true)
		return ;
	get_timestamp(dinner);
	pthread_mutex_lock(dinner->print_mutex);
	printf("%ld %d is sleeping\n", dinner->timestamp, dinner->philo_id);
	pthread_mutex_unlock(dinner->print_mutex);
	usleep(ms * 1000);
}
