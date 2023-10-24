/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbussier <gbussier@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 19:08:43 by gbussier          #+#    #+#             */
/*   Updated: 2023/10/03 19:08:47 by gbussier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

void	monitor(t_philo *tail, t_cond argument)
{
	while (1)
	{
		if (check_death_table(tail, argument) == 1)
			break ;
		else if (check_meal(tail, argument) == 1)
			break ;
		usleep(2000);
	}
}

int	check_death_table(t_philo *philo, t_cond argument)
{
	t_philo	*curr;
	int		i;

	i = 0;
	curr = philo;
	pthread_mutex_lock(&philo->mutx_help->mtx_death);
	if (curr->mutx_help->stat_death > 0)
	{
		pthread_mutex_unlock(&philo->mutx_help->mtx_death);
		return (1);
	}
	pthread_mutex_unlock(&philo->mutx_help->mtx_death);
	return (0);
}

int	check_meal(t_philo *philo, t_cond argument)
{
	t_philo	*curr;

	curr = philo;
	if (argument.argc != 6)
		return (0);
	pthread_mutex_lock(&philo->mutx_help->mtx_meal);
	if (philo->mutx_help->count_meal >= philo->arg.number_of_philosophers)
	{
		pthread_mutex_lock(&(curr->mutx_help->mtx_death));
		curr->mutx_help->stat_death = 1;
		pthread_mutex_unlock(&(curr->mutx_help->mtx_death));
		pthread_mutex_unlock(&philo->mutx_help->mtx_meal);
		return (1);
	}
	pthread_mutex_unlock(&philo->mutx_help->mtx_meal);
	return (0);
}
