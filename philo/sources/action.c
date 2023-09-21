/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbussier <gbussier@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 16:58:17 by gbussier          #+#    #+#             */
/*   Updated: 2023/09/21 16:59:41 by gbussier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

int	eating_function(philo_t *Philo)
{
	if (Philo->PhiloNumber % 2 == 0)
	{
		pthread_mutex_lock(&Philo->Fork);
		Philo->ForkStatus = 1;
		print_message(Philo, "has taken a fork", gettimestamp(Philo->arguments));
		pthread_mutex_lock(&Philo->NextPhilo->Fork);
		Philo->NextPhilo->ForkStatus = 1;
		print_message(Philo, "has taken a fork", gettimestamp(Philo->arguments));
	}
	else
	{
		pthread_mutex_lock(&Philo->NextPhilo->Fork);
		Philo->NextPhilo->ForkStatus = 1;
		print_message(Philo, "has taken a fork", gettimestamp(Philo->arguments));
		pthread_mutex_lock(&Philo->Fork);
		Philo->ForkStatus = 1;
		print_message(Philo, "has taken a fork", gettimestamp(Philo->arguments));
	}
	return (1);
}

int	sleeping_function(philo_t *Philo)
{
	print_message(Philo, "is sleeping", gettimestamp(Philo->arguments));
	usleep(Philo->arguments.time_to_sleep * 1000);
	return (1);
}
