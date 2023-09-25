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

int	eating2(t_philo *philo, long *last_meal_date)
{
	print_message(philo, "is eating", gettimestamp(philo->arg));
	philo->nb_of_meal++;
	*last_meal_date = gettimestamp(philo->arg);
	if (check_death(philo, *last_meal_date, "eat"))
		return (0);
	usleep(philo->arg.time_to_eat * 1000);
	if (check_death(philo, *last_meal_date, "death"))
		return (0);
	philo->fork_tatus = 0;
	pthread_mutex_unlock(&philo->fork);
	philo->next_philo->fork_tatus = 0;
	pthread_mutex_unlock(&philo->next_philo->fork);
	return (1);
}

int	eating_function(t_philo *philo, long *last_meal_date)
{
	if (philo->philo_nb % 2 == 0)
	{
		pthread_mutex_lock(&philo->fork);
		philo->fork_tatus = 1;
		print_message(philo, "has taken a fork", gettimestamp(philo->arg));
		pthread_mutex_lock(&philo->next_philo->fork);
		philo->next_philo->fork_tatus = 1;
		print_message(philo, "has taken a fork", gettimestamp(philo->arg));
	}
	else
	{
		pthread_mutex_lock(&philo->next_philo->fork);
		philo->next_philo->fork_tatus = 1;
		print_message(philo, "has taken a fork", gettimestamp(philo->arg));
		pthread_mutex_lock(&philo->fork);
		philo->fork_tatus = 1;
		print_message(philo, "has taken a fork", gettimestamp(philo->arg));
	}
	if (!eating2(philo, last_meal_date))
		return (0);
	return (1);
}

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

int	thinking_function(t_philo *philo, long *last_meal_date, int *flag)
{
	print_message(philo, "is thinking", gettimestamp(philo->arg));
	if (*flag == 1)
		usleep(1000);
	else if (*flag == 0 && philo->philo_nb % 2)
	{
		usleep(1000);
		*flag = 1;
	}
	while ((philo->fork_tatus + philo->next_philo->fork_tatus) != 0)
	{
		if (check_death(philo, *last_meal_date, "death"))
			return (0);
		usleep(100);
	}
	return (1);
}
