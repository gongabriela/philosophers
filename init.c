/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggoncalv <ggoncalv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 11:08:13 by ggoncalv          #+#    #+#             */
/*   Updated: 2025/09/13 11:08:13 by ggoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_struct_server(t_monitor *server)
{
	//memset tudo?? pro philos nao apontar pra null talvez
}

/*
* fill args info in struct
* assign forks. table is circular, so the last member needs to take last fork
*/
void	init_struct_philos(t_philos *philo, t_monitor *server, char **argv)
{
	int	i;

	i = -1;
	while (++i < ft_atol(argv[1]))
	{
		fill_args(&philo[i], argv);
		philo[i].id = i + 1;
		if (i == 0)
			philo[i].left_fork = server->forks_array[philo[i].number_of_philos - 1];
		else
			philo[i].left_fork = server->forks_array[i - 1];
		philo[i].right_fork = server->forks_array[i];
	}
}

void	fill_args(t_philos *philo, char **argv)
{
	philo->number_of_philos = ft_atol(argv[1]);
	philo->time_to_die = ft_atol(argv[2]);
	philo->time_to_eat = ft_atol(argv[3]);
	philo->time_to_sleep = ft_atol(argv[4]);
	if (argv[5])
		philo->must_eat = ft_atol(argv[5]);
	else
		philo->must_eat = -1;
}

void	init_mutexes(t_monitor *server, t_philos *philo)
{
	int	i;

	(void)philo;
	i = -1;
	while (++i < philo[0].number_of_philos)
		pthread_mutex_init(&server->forks_array[i], NULL);
}

void	init_threads(t_monitor *server, t_philos *philo)
{
	int	i;

	if (pthread_create(&server->thread, NULL, server_routine, server))
		ft_free_and_destroy();
	i = -1;
	while (++i < philo[0].number_of_philos)
	{
		if (pthread_create(&philo[i].thread, NULL, routine, &philo[i]))
			ft_free_and_destroy();
	}
	i = -1;
	while (++i < dinner[0].number_of_philos)
		pthread_join(&philo[i].thread, NULL);
	pthread_join(&server->thread);
}
