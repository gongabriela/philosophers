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
	get_start_time_in_ms(dinner);
	if (dinner->philo_id % 2 == 0)
		think(dinner, dinner->time_to_eat);
	while (1)
	{
		if (get_death_info_dinner(dinner) == true)
			break ;
		grab_forks(dinner);
		eat(dinner, dinner->time_to_eat);
		ft_sleep(dinner, dinner->time_to_sleep);
		if (get_death_info_dinner(dinner) == true)
			break ;
		think(dinner, dinner->time_to_eat);
	}
	return (NULL);
}

void	get_start_time_in_ms(t_struct *dinner)
{
	long	start_time_ms;

	start_time_ms = dinner->start_time.tv_sec * 1000 + dinner->start_time.tv_usec / 1000;
	dinner->last_meal = start_time_ms;
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
		pthread_mutex_unlock(dinner->print_mutex);
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
