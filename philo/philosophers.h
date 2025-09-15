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
# define MAX 200
# include <stdio.h>
# include <limits.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdbool.h>
# include <unistd.h>

//philos struct ------------------------------------------------------------

typedef struct s_philos
{
	long			number_of_philos;
	long			time_to_eat;
	long			time_to_sleep;
	long			time_to_die;
	long			must_eat;
	pthread_t		thread;
	int				id;
	long			start_time;
	int				philo_id;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;

	bool			*begin;
	pthread_mutex_t	*begin_mutex;

	bool			*died;
	pthread_mutex_t	*died_mutex;

	pthread_mutex_t	*print_mutex;

	long			last_meal;
	pthread_mutex_t	last_meal_mutex;

	bool			eating;
	pthread_mutex_t	eating_mutex;

	int				meals_eaten;
	pthread_mutex_t	meals_eaten_mutex;
}	t_philos;

//server struct ----------------------------------------------------------------

typedef struct s_monitor
{
	t_philos		*philo;
	pthread_mutex_t	*forks_array;
	pthread_t		thread;

	bool			begin;
	pthread_mutex_t	begin_mutex;

	bool			died;
	pthread_mutex_t	died_mutex;

	pthread_mutex_t	print_mutex;

}	t_monitor;

// ---------------------------------parsing------------------------------------

int		check_for_overflow(char **argv);
long	ft_atol(const char *str);
int		ft_is_all_digit(char **argv);
int		parse_args(int argc, char **argv);

// -------------------------init structs----------------------------------------

void	init_struct_server(t_monitor *server, pthread_mutex_t *forks,
			t_philos *philo);
void	init_struct_philos(t_philos *philo, t_monitor *server, char **argv);
void	fill_args(t_philos *philo, char **argv);
void	init_mutexes(t_monitor *server, t_philos *philo);
void	init_threads(t_monitor *server, t_philos *philo);

// -------------------------routines--------------------------------------------

void	*philo_routine(void *arg);
void	*server_routine(void *arg);
void	wait_to_begin(t_philos *philo);
int		check_death_all(t_philos *philo);
int		finished_eating(t_philos *philo);

// -------------------------time functions------------------------------------

long	get_current_time(void);
void	ft_usleep(long time_in_ms, t_philos *philo);
void	get_start_time(t_philos *philo);

// -------------------------checker functions----------------------------------

bool	check_death(t_philos *philo);

// -------------------------action functions-----------------------------------

int		grab_forks(t_philos *philo);
int		eat(t_philos *philo);
void	release_forks(t_philos *philo);
void	ft_sleep(t_philos *philo);
void	think(t_philos *philo);
void	table_for_one(t_philos *philo);

// -------------------------print functions------------------------------------

void	print_msg(char *msg, t_philos *philo);

// ------------------------cleanup----------------------------------------------

void	free_and_destroy(char *msg, t_monitor *server, t_philos *philo);

#endif