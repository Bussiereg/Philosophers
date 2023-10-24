/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleeping.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbussier <gbussier@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 09:53:19 by gbussier          #+#    #+#             */
/*   Updated: 2023/10/04 09:53:21 by gbussier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	sleeping_function(t_philo *philo, long *last_meal_date)
{
	if (check_death(philo, *last_meal_date, "sleep"))
		return (0);
	print_message(philo, "is sleeping", gettimestamp(philo->arg));
	usleep(philo->arg.time_to_sleep * 1000);
	if (check_death(philo, *last_meal_date, "death"))
		return (0);
	return (1);
}
