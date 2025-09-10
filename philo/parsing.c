/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggoncalv <ggoncalv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 09:31:10 by ggoncalv          #+#    #+#             */
/*   Updated: 2025/09/09 09:31:10 by ggoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/philosophers.h"

int	parse_args(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		return (1);
	if (ft_is_all_digit(argv) == 1)
		return (1);
	if (check_for_overflow(argv) == 1)
		return (1);
	if (ft_atoi(argv[1]) == 0 || ft_atoi(argv[1]) > 200)
		return (1);
	if (ft_atoi(argv[2]) < 60 || ft_atoi(argv[3]) < 60 || ft_atoi(argv[4]) < 60)
		return (1);
	return (0);
}
