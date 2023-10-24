/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbussier <gbussier@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 17:00:08 by gbussier          #+#    #+#             */
/*   Updated: 2023/09/25 15:43:38 by gbussier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

int	check_sleep_death(t_philo *philo, long last_meal_date, char *activity)
{
	if (ft_strncmp(activity, "sleep", ft_strlen(activity)) == 0)
	{
		if (time_since_last_meal(philo->arg, last_meal_date) 
			+ philo->arg.time_to_sleep > philo->arg.time_to_die)
		{
			print_message(philo, "is sleeping", gettimestamp(philo->arg));
			usleep((philo->arg.time_to_die
					- time_since_last_meal(philo->arg, last_meal_date)) * 1000);
			print_message(philo, "died", gettimestamp(philo->arg));
			pthread_mutex_lock(&philo->mutx_help->mtx_death);
			philo->mutx_help->stat_death = 1;
			pthread_mutex_unlock(&philo->mutx_help->mtx_death);
			return (1);
		}
	}
	return (0);
}

int	check_others_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->mutx_help->mtx_death);
	if (philo->mutx_help->stat_death > 0)
	{
		pthread_mutex_unlock(&philo->mutx_help->mtx_death);
		return (1);
	}
	pthread_mutex_unlock(&philo->mutx_help->mtx_death);
	return (0);
}

int	check_eat_death(t_philo *philo, long lastmeal, char *activity)
{
	if (ft_strncmp(activity, "eat", ft_strlen(activity)) == 0)
	{
		if (time_since_last_meal(philo->arg, lastmeal) 
			+ philo->arg.time_to_eat > philo->arg.time_to_die)
		{
			usleep((philo->arg.time_to_die
					- time_since_last_meal(philo->arg, lastmeal)) * 1000);
			print_message(philo, "died", gettimestamp(philo->arg));
			pthread_mutex_lock(&philo->mutx_help->mtx_death);
			philo->mutx_help->stat_death = 1;
			pthread_mutex_unlock(&philo->mutx_help->mtx_death);
			return (1);
		}
	}
	return (0);
}

int	check_death_death(t_philo *philo, long lastmeal, char *activity)
{
	if (ft_strncmp(activity, "death", ft_strlen(activity)) == 0)
	{
		if (time_since_last_meal(philo->arg, lastmeal) > philo->arg.time_to_die)
		{
			print_message(philo, "died", gettimestamp(philo->arg));
			pthread_mutex_lock(&philo->mutx_help->mtx_death);
			philo->mutx_help->stat_death = 1;
			pthread_mutex_unlock(&philo->mutx_help->mtx_death);
			return (1);
		}
	}
	return (0);
}

int	check_death(t_philo *philo, long lastmeal, char *activity)
{
	if (check_others_death(philo) == 1)
		return (1);
	else if (check_sleep_death(philo, lastmeal, activity) == 1)
		return (1);
	else if (check_eat_death(philo, lastmeal, activity) == 1)
		return (1);
	else if (check_death_death(philo, lastmeal, activity) == 1)
		return (1);
	return (0);
}
