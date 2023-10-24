/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbussier <gbussier@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 09:54:00 by gbussier          #+#    #+#             */
/*   Updated: 2023/10/04 09:54:03 by gbussier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

int	eating2(t_philo *philo, long *last_meal_date)
{
	print_message(philo, "is eating", gettimestamp(philo->arg));
	philo->nb_of_meal++;
	if (philo->nb_of_meal == philo->arg.number_of_meal)
	{
		pthread_mutex_lock(&philo->mutx_help->mtx_meal);
		philo->mutx_help->count_meal++;
		pthread_mutex_unlock(&philo->mutx_help->mtx_meal);
	}
	*last_meal_date = gettimestamp(philo->arg);
	if (check_death(philo, *last_meal_date, "eat"))
		return (0);
	usleep(philo->arg.time_to_eat * 1000);
	if (check_death(philo, *last_meal_date, "death"))
		return (0);
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_lock(&philo->mtx_stat_fork);
	philo->stat_fork = 0;
	pthread_mutex_unlock(&philo->mtx_stat_fork);
	pthread_mutex_unlock(&philo->next_philo->fork);
	pthread_mutex_lock(&philo->next_philo->mtx_stat_fork);
	philo->next_philo->stat_fork = 0;
	pthread_mutex_unlock(&philo->next_philo->mtx_stat_fork);
	return (1);
}

int	take_fork_even(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork);
	pthread_mutex_lock(&philo->mtx_stat_fork);
	philo->stat_fork = 1;
	print_message(philo, "has taken a fork", gettimestamp(philo->arg));
	pthread_mutex_unlock(&philo->mtx_stat_fork);
	pthread_mutex_lock(&philo->next_philo->fork);
	pthread_mutex_lock(&philo->next_philo->mtx_stat_fork);
	philo->next_philo->stat_fork = 1;
	print_message(philo, "has taken a fork", gettimestamp(philo->arg));
	pthread_mutex_unlock(&philo->next_philo->mtx_stat_fork);
	return (1);
}

int	take_fork_odd(t_philo *philo)
{
	pthread_mutex_lock(&philo->next_philo->fork);
	pthread_mutex_lock(&philo->next_philo->mtx_stat_fork);
	philo->next_philo->stat_fork = 1;
	print_message(philo, "has taken a fork", gettimestamp(philo->arg));
	pthread_mutex_unlock(&philo->next_philo->mtx_stat_fork);
	pthread_mutex_lock(&philo->fork);
	pthread_mutex_lock(&philo->mtx_stat_fork);
	philo->stat_fork = 1;
	print_message(philo, "has taken a fork", gettimestamp(philo->arg));
	pthread_mutex_unlock(&philo->mtx_stat_fork);
	return (1);
}

int	eating_function(t_philo *philo, long *last_meal_date)
{
	if (philo->philo_nb % 2 == 0)
		take_fork_even(philo);
	else
		take_fork_odd(philo);
	if (!eating2(philo, last_meal_date))
	{
		pthread_mutex_unlock(&philo->fork);
		pthread_mutex_unlock(&philo->next_philo->fork);
		return (0);
	}
	return (1);
}
