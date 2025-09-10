/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggoncalv <ggoncalv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 17:45:50 by ggoncalv          #+#    #+#             */
/*   Updated: 2025/09/10 17:45:50 by ggoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/philosophers.h"

//melhorar esta funcao
void	ft_free_and_destroy(char *error_msg, pthread_t *philos, pthread_mutex_t *forks, t_struct *dinner, t_monitor *server)
{
	int	i;

	i = 0;
	if (error_msg)
		printf("%s\n", error_msg);
	while(i < dinner[0].number_of_philos)
	{
		pthread_join(philos[i], NULL);
		i++;
	}
	i = 0;
	while (i < dinner[0].number_of_philos)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
	pthread_mutex_destroy(&server->print_mutex);
}
