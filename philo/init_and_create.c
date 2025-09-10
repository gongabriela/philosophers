/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_and_create.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggoncalv <ggoncalv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 17:45:01 by ggoncalv          #+#    #+#             */
/*   Updated: 2025/09/10 17:45:01 by ggoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/philosophers.h"

void	init_struct(t_struct *dinner, pthread_t *philos, pthread_mutex_t *forks, char **argv)
{
	int	i;
	int	number_of_philos;

	i = 0;
	number_of_philos = ft_atoi(argv[1]);
	while (i < number_of_philos)
	{
		dinner[i].number_of_philos = number_of_philos;
		dinner[i].time_to_die = ft_atoi(argv[2]);
		dinner[i].time_to_eat = ft_atoi(argv[3]);
		dinner[i].time_to_sleep = ft_atoi(argv[4]);
		if (argv[5])
			dinner[i].must_eat = ft_atoi(argv[5]);
		else
			dinner[i].must_eat = -1;
		dinner[i].philos_array = philos;
		dinner[i].forks_array = forks;
		dinner[i].philo_id = i + 1;
		if (i == 0)
			dinner[i].left_fork = &forks[number_of_philos - 1];
		else
			dinner[i].left_fork = &forks[i - 1];
		dinner[i].right_fork = &forks[i];
		i++;
	}
}

void	create_forks(pthread_mutex_t *forks, t_struct *dinner)
{
	int	i;

	i = 0;
	while (i < dinner[0].number_of_philos)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
}

void	create_print_mutex(pthread_mutex_t *print_mutex, t_struct *dinner)
{
	int	i;

	pthread_mutex_init(print_mutex, NULL);
	i = 0;
	while (i < dinner[0].number_of_philos)
	{
		dinner[i].print_mutex = print_mutex;
		i++;
	}
}

void	begin_dinner(pthread_t *philos, t_struct *dinner, t_monitor *server)
{
	int	i;

	i = 0;
	get_start_time(dinner);
	while (i < dinner[0].number_of_philos)
	{
		if (pthread_create(&philos[i], NULL, routine, &dinner[i]))
			ft_free_and_destroy("thread creation failed", philos, dinner[i].forks_array, dinner, server);
		i++;
	}
}
