/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbussier <gbussier@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 19:20:30 by gbussier          #+#    #+#             */
/*   Updated: 2023/10/03 19:20:32 by gbussier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_input( int argc, char **argv)
{
	if (argc < 5 || argc > 6)
	{
		printf("1: ./philo\n2: number_of_philosophers\n3: time_to_die\n");
		printf("4: time_to_eat\n5: time_to_sleep\n");
		printf("6: [number_of_times_each_philosophers_must_eat]\n");
		return (0);
	}
	if (ft_atoi(argv[1]) <= 0)
		return (0);
	if (argc == 6)
	{
		if (ft_atoi(argv[5]) == 0)
			return (0);
	}
	return (1);
}
