/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggoncalv <ggoncalv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 12:12:50 by ggoncalv          #+#    #+#             */
/*   Updated: 2025/04/15 12:12:50 by ggoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <limits.h>
# include <sys/time.h>
#  define MAX 200
//--------------------------main struct---------------------------------------

typedef struct s_struct
{
	int				number_of_philos;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_die;
	int				must_eat;

	pthread_t		*philos_array; //not sure if we need that here
	pthread_mutex_t *forks_array; //not sure if we need that here

//	bool			*death_flag;

	struct timeval	start_time;
	struct timeval	current_time;
	//struct timeval	last_meal;
	long			timestamp;

	int				philo_id;
	pthread_mutex_t *left_fork;
	pthread_mutex_t *right_fork;

	pthread_mutex_t	*print_mutex;
	//pthread_mutex_t	*death_flag_mutex;
	//pthread_mutex_t	*last_meal_mutex;

} t_struct;

typedef struct s_monitor
{
	pthread_t		server;
	t_struct		*dinner;
	//bool			death_flag;
	//pthread_mutex_t	death_flag_mutex;
	pthread_mutex_t	print_mutex;
	//pthread_mutex_t last_meal_mutex;
} t_monitor;

//-----------------------------parsing----------------------------------------

int			parse_args(int argc, char **argv);
int			ft_isdigit(int c);
int			ft_is_all_digit(char **argv);
long long	ft_atoll(const char *str);
int			check_for_overflow(char **argv);
int			ft_atoi(const char *str);

//-----------------------init struct-----------------------------------------

void	init_struct(t_struct *dinner, pthread_t *philos, pthread_mutex_t *forks, char **argv);
void	create_forks(pthread_mutex_t *forks, t_struct *dinner);
void	begin_dinner(pthread_t *philos, t_struct *dinner, t_monitor *server);
void	*routine(void *arg);
void	ft_free_and_destroy(char *error_msg, pthread_t *philos, pthread_mutex_t *forks, t_struct *dinner, t_monitor *server);
void	create_print_mutex(pthread_mutex_t *print_mutex, t_struct *dinner);

// ------------------ actions ---------------------------------------------

void	think(t_struct *dinner, int	ms);
void	ft_sleep(t_struct *dinner, int ms);
void	eat(t_struct *dinner, int ms);
void	grab_forks(t_struct *dinner);

//-----------------time----------------------------------------------------

void	get_timestamp(t_struct *dinner);
void	get_current_time(t_struct *dinner);
void	get_start_time(t_struct *dinner);

//--------------------death check ---------------------------------------

void	create_death_flag_mutex(pthread_mutex_t *death_flag, t_monitor *dinner, t_monitor *server);

// --------------------server-------------------------------------------

void	init_server(t_struct *dinner, t_monitor *server);
void	*server_routine(void *arg);
#endif