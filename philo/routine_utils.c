/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggoncalv <ggoncalv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 12:16:02 by ggoncalv          #+#    #+#             */
/*   Updated: 2025/09/11 14:47:31 by ggoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/philosophers.h"

bool	get_death_info_dinner(t_struct *dinner)
{
	pthread_mutex_lock(dinner->death_mutex);
	if (*(dinner->death) == true)
		return (pthread_mutex_unlock(dinner->death_mutex), true);
	return (pthread_mutex_unlock(dinner->death_mutex), false);
}

void	update_last_meal(t_struct *dinner)
{
	pthread_mutex_lock(&dinner->last_meal_mutex);
	dinner->last_meal = dinner->timestamp;
	pthread_mutex_unlock(&dinner->last_meal_mutex);
}
