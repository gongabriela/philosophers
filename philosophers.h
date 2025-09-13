/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggoncalv <ggoncalv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 10:50:38 by ggoncalv          #+#    #+#             */
/*   Updated: 2025/09/13 10:50:38 by ggoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <limits.h>

//server struct
typedef struct s_monitor
{
	t_struct		*dinner;
	pthread_mutex_t	*forks_array;
	pthread_t		thread;
} t_monitor;

//philos struct
typedef struct s_philoa
{
	long			number_of_philos;
	long			time_to_eat;
	long			time_to_sleep;
	long			time_to_die;
	long			must_eat;
	pthread_t		thread;
	int				id;
	struct timeval	start_time; //ou ja guarda em ms?
	int				philo_id;
	pthread_mutex_t *left_fork;
	pthread_mutex_t *right_fork;
} t_philos;

// ---------------------------------parsing------------------------------------

int		check_for_overflow(char **argv);
long	ft_atol(const char *str);
int		ft_is_all_digit(char **argv);
int		parse_args(int argc, char **argv);

// -------------------------init structs----------------------------------------

#endif