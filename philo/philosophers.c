/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggoncalv <ggoncalv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 12:12:34 by ggoncalv          #+#    #+#             */
/*   Updated: 2025/04/15 12:12:34 by ggoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/philosophers.h"

int	main(int argc, char **argv)
{
	t_struct		dinner[MAX];
	t_monitor		server;
	pthread_t		philos[MAX];
	pthread_mutex_t	forks[MAX];

	if (parse_args(argc, argv) == 1)
		return (printf("Error: invalid arguments\n"), 1);
	init_struct_dinner(dinner, philos, forks, argv);
	init_struct_server(dinner, &server);
	init_mutexes(forks, dinner, &server);
	begin_dinner(philos, dinner, &server);
	ft_free_and_destroy(NULL, philos, forks, dinner, &server);
	return (0);
}
