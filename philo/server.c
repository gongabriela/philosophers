/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggoncalv <ggoncalv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 12:03:25 by ggoncalv          #+#    #+#             */
/*   Updated: 2025/09/10 12:03:25 by ggoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/philosophers.h"

/*void	init_server(t_struct *dinner, t_monitor *server)
{
    server->dinner = dinner;
    server->death_flag = dinner[0].death_flag; // int *death_flag
    server->death_flag_mutex = dinner[0].death_flag_mutex; // pthread_mutex_t *
    server->print_mutex = dinner[0].print_mutex; // pthread_mutex_t *
    if (pthread_create(server->server, NULL, &server_routine, server))
        ft_free_destroy("monitor thread creation failed", dinner[0].philos_array, dinner[0].forks_array, dinner);
}

void	*server_routine(void *arg)
{
    t_monitor	*server = (t_monitor *)arg;
    int			i;

    while (1)
    {
        // Check if death flag is set (with mutex)
        pthread_mutex_lock(server->death_flag_mutex);
        if (*(server->death_flag))
        {
            pthread_mutex_unlock(server->death_flag_mutex);
            break;
        }
        pthread_mutex_unlock(server->death_flag_mutex);

        i = 0;
        while (i < server->dinner[0].number_of_philos)
        {
            if (check_if_philo_has_died(server, &server->dinner[i]))
            {
                pthread_mutex_lock(server->death_flag_mutex);
                *(server->death_flag) = 1;
                pthread_mutex_unlock(server->death_flag_mutex);

                pthread_mutex_lock(server->print_mutex);
                printf("[%ld] %d has died\n", get_timestamp(&server->dinner[i]), server->dinner[i].philo_id);
                pthread_mutex_unlock(server->print_mutex);
                return (NULL);
            }
            i++;
        }
        usleep(1000); // avoid busy waiting
    }
    return (NULL);
}

int	check_if_philo_has_died(t_monitor *server, t_struct *dinner)
{
    long	current_time;
    long	time_since_last_meal;

    current_time = get_timestamp(dinner);
    pthread_mutex_lock(dinner->meal_mutex); // protect access to last_meal
    time_since_last_meal = current_time - dinner->last_meal;
    pthread_mutex_unlock(dinner->meal_mutex);

    if (time_since_last_meal > dinner->time_to_die)
        return (1);
    return (0);
}*/
