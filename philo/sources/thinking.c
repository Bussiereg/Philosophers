/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thinking.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbussier <gbussier@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 09:51:34 by gbussier          #+#    #+#             */
/*   Updated: 2023/10/04 09:51:35 by gbussier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	check_mtx_stat_fork(t_philo *philo)
{
	if (philo->philo_nb % 2 == 0)
	{
		pthread_mutex_lock(&philo->mtx_stat_fork);
		pthread_mutex_lock(&philo->next_philo->mtx_stat_fork);
	}
	else
	{
		pthread_mutex_lock(&philo->next_philo->mtx_stat_fork);
		pthread_mutex_lock(&philo->mtx_stat_fork);
	}
}

void	init_think_ft(t_philo *philo, int *flag)
{
	if (*flag == 1)
		usleep(1000);
	else if (*flag == 0 && philo->philo_nb % 2)
	{
		usleep(1000);
		*flag = 1;
	}
}

int	thinking_function(t_philo *philo, long *last_meal_date, int *flag)
{
	print_message(philo, "is thinking", gettimestamp(philo->arg));
	init_think_ft(philo, flag);
	while (1)
	{
		check_mtx_stat_fork(philo);
		if (philo->stat_fork + philo->next_philo->stat_fork == 0)
			break ;
		else
		{
			if (check_death(philo, *last_meal_date, "death"))
			{
				pthread_mutex_unlock(&philo->mtx_stat_fork);
				pthread_mutex_unlock(&philo->next_philo->mtx_stat_fork);
				return (0);
			}
		}
		pthread_mutex_unlock(&philo->mtx_stat_fork);
		pthread_mutex_unlock(&philo->next_philo->mtx_stat_fork);
		usleep(100);
	}
	pthread_mutex_unlock(&philo->mtx_stat_fork);
	pthread_mutex_unlock(&philo->next_philo->mtx_stat_fork);
	return (1);
}
