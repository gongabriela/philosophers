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

void	init_struct_server(t_monitor *server, pthread_mutex_t *forks,
		t_philos *philo)
{
	server->forks_array = forks;
	server->philo = philo;
	server->begin = false;
	server->died = false;
}

void	init_struct_philos(t_philos *philo, t_monitor *server, char **argv)
{
	int	i;

	i = -1;
	while (++i < ft_atol(argv[1]))
	{
		fill_args(&philo[i], argv);
		philo[i].id = i + 1;
		if (i == 0)
			philo[i].left_fork
				= &server->forks_array[philo[i].number_of_philos - 1];
		else
			philo[i].left_fork = &server->forks_array[i - 1];
		philo[i].right_fork = &server->forks_array[i];
		philo[i].begin = &server->begin;
		philo[i].begin_mutex = &server->begin_mutex;
		philo[i].died = &server->died;
		philo[i].died_mutex = &server->died_mutex;
		philo[i].print_mutex = &server->print_mutex;
		philo[i].eating = false;
		philo[i].meals_eaten = 0;
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
	{
		pthread_mutex_init(&server->forks_array[i], NULL);
		pthread_mutex_init(&philo[i].last_meal_mutex, NULL);
		pthread_mutex_init(&philo[i].eating_mutex, NULL);
		pthread_mutex_init(&philo[i].meals_eaten_mutex, NULL);
	}
	pthread_mutex_init(&server->begin_mutex, NULL);
	pthread_mutex_init(&server->died_mutex, NULL);
	pthread_mutex_init(&server->print_mutex, NULL);
}

void	init_threads(t_monitor *server, t_philos *philo)
{
	int	i;

	if (pthread_create(&server->thread, NULL, server_routine, server))
		free_and_destroy("Error creating server thread", NULL, NULL);
	i = -1;
	while (++i < philo[0].number_of_philos)
	{
		if (pthread_create(&philo[i].thread, NULL, philo_routine, &philo[i]))
			free_and_destroy("Error creating philosopher thread", NULL, NULL);
	}
	get_start_time(philo);
	pthread_mutex_lock(&server->begin_mutex);
	server->begin = true;
	pthread_mutex_unlock(&server->begin_mutex);
	i = -1;
	while (++i < philo[0].number_of_philos)
		pthread_join(philo[i].thread, NULL);
	pthread_join(server->thread, NULL);
}
