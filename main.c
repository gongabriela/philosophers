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
	init_struct_server(&server);
	init_struct_philos(&philos, &server, argv);
	init_mutexes(&server, &philos);
	init_threads(&server, &philos);
	free_and_destroy(NULL, &server, &philos);
	return (0);
}
