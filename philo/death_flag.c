/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_flag.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggoncalv <ggoncalv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 17:49:34 by ggoncalv          #+#    #+#             */
/*   Updated: 2025/09/10 17:49:34 by ggoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/philosophers.h"

/*void	create_death_flag_mutex(pthread_mutex_t *death_flag, t_monitor *dinner, t_monitor *server)
{
	int				i;
	bool			death_bool;

	pthread_mutex_init(&server->death_flag, NULL);
	death_bool = false;
	i = 0;
	while(i < dinner[0].number_of_philos)
	{
		dinner[i].death_flag = &death_bool;
		dinner[i].death_flag_mutex = &death_flag;
	}
}*/
