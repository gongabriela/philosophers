/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggoncalv <ggoncalv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 11:37:53 by ggoncalv          #+#    #+#             */
/*   Updated: 2025/09/13 11:37:53 by ggoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	free_and_destroy(char *msg, t_monitor *server, t_philos *philo)
{
	int	i;

	if (msg)
		printf("%s\n", msg);
	i = -1;
	while (++i < philo[0].number_of_philos)
	{
		pthread_mutex_destroy(&server->forks_array[i]);
		pthread_mutex_destroy(&philo[i].last_meal_mutex);
		pthread_mutex_destroy(&philo[i].eating_mutex);
		pthread_mutex_destroy(&philo[i].meals_eaten_mutex);
	}
	pthread_mutex_destroy(&server->begin_mutex);
	pthread_mutex_destroy(&server->died_mutex);
	pthread_mutex_destroy(&server->print_mutex);
}
