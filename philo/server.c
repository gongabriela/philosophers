/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggoncalv <ggoncalv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 12:03:25 by ggoncalv          #+#    #+#             */
/*   Updated: 2025/09/10 12:03:25 by ggoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/philosophers.h"

void	*server_routine(void *arg)
{
	t_monitor	*server = (t_monitor *)arg;
	bool		death_copy;
	int			i;

	while (1)
	{
		death_copy = get_death_info(server); //abrir o death com mutex, pegar info, deslockar death
		if (death_copy == true)
		{
			break ;
		}
		i = 0;
		while (i < server->dinner[0].number_of_philos)
		{
			if (ate_all(&server->dinner[i]))
				return (NULL);
			if (check_if_philo_has_died(server, &server->dinner[i]))
			{
				change_death(server); //mudar a flag death para true
				pthread_mutex_lock(&server->print_mutex);
				printf("%ld %d has died\n", get_timestamp_server(server), i + 1); //printar msg de morte
				pthread_mutex_unlock(&server->print_mutex);
				return (NULL);
			}
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}

int	ate_all(t_struct *dinner)
{
	static int all_finished = 0;

	if (dinner->must_eat == -1)
		return (0);
	pthread_mutex_lock(&dinner->finished_mutex);
	if (dinner->finished == 1 && dinner->counted == 0)
	{
		all_finished++;
		dinner->counted = 1;
	}
	pthread_mutex_unlock(&dinner->finished_mutex);
	if (all_finished == dinner->number_of_philos)
		return (1);
	return (0);
}
bool	get_death_info(t_monitor *server)
{
	pthread_mutex_lock(&server->death_mutex);
	if (server->death == true)
		return (pthread_mutex_unlock(&server->death_mutex), true);
	return (pthread_mutex_unlock(&server->death_mutex), false);
}

void	change_death(t_monitor *server)
{
	pthread_mutex_lock(&server->death_mutex);
	server->death = true;
	pthread_mutex_unlock(&server->death_mutex);
}

long	get_timestamp_server(t_monitor *server)
{
	struct timeval	current_time;
	long	seconds;
	long	useconds;
	long	timestamp;

	gettimeofday(&current_time, NULL);

	seconds = current_time.tv_sec - server->start_time.tv_sec;
	useconds = current_time.tv_usec - server->start_time.tv_usec;
	timestamp = seconds * 1000 + useconds / 1000;
	server->timestamp = timestamp;
	return (timestamp);
}

//precisamos implementar last_meal para implementar essa funcao!
int	check_if_philo_has_died(t_monitor *server, t_struct *dinner)
{
	long	current_time;
	long	time_since_last_meal;

	pthread_mutex_lock(&dinner->finished_mutex);
	if (dinner->finished == 1)
	{
		pthread_mutex_unlock(&dinner->finished_mutex);
		return (0);
	}
	pthread_mutex_unlock(&dinner->finished_mutex);
	current_time = get_timestamp_server(server); //aqui vai ser igual! shared resources. usar o time of death, mudar o nome talvez
	pthread_mutex_lock(&dinner->last_meal_mutex); // protect access to last_meal
	time_since_last_meal = current_time - dinner->last_meal;
	pthread_mutex_unlock(&dinner->last_meal_mutex);
	if (time_since_last_meal > dinner->time_to_die)
		return (1);
	return (0);
}
