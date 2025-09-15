/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggoncalv <ggoncalv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 10:50:29 by ggoncalv          #+#    #+#             */
/*   Updated: 2025/09/13 10:50:29 by ggoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_philos		philos[MAX];
	pthread_mutex_t	forks[MAX];
	t_monitor		server;

	if (parse_args(argc, argv) == 1)
		return (printf("Error: invalid arguments\n"), 1);
	init_struct_server(&server, forks, philos);
	init_struct_philos(philos, &server, argv);
	init_mutexes(&server, philos);
	init_threads(&server, philos);
	free_and_destroy(NULL, &server, philos);
	return (0);
}

void	print_msg(char *msg, t_philos *philo)
{
	long	timestamp;

	if (check_death(philo) == true)
		return ;
	timestamp = get_current_time() - philo->start_time;
	pthread_mutex_lock(philo->print_mutex);
	printf("%ld %d %s\n", timestamp, philo->id, msg);
	pthread_mutex_unlock(philo->print_mutex);
}
