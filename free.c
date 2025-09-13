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

void	ft_free_and_destruy(char *msg, t_monitor *server, t_philos *philo)
{
	int	i;

	if (msg)
		printf("%s\n", msg);
	i = 0;
	while (i < philo[0].number_of_philos)
	{
		pthread_mutex_destroy(&server->forks_array[i]);
	}
}