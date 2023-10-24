/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_sim.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbussier <gbussier@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 19:13:06 by gbussier          #+#    #+#             */
/*   Updated: 2023/10/03 19:13:07 by gbussier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

void	thread_join(t_philo *tail)
{
	int		i;
	t_philo	*curr;

	curr = tail;
	i = 0;
	while (i < curr->arg.number_of_philosophers)
	{
		pthread_join(curr->philosopher, NULL);
		curr = curr->next_philo;
		i++;
	}
}

void	close_simulation(t_philo *tail, t_cond argument)
{
	int		i;
	t_philo	*curr;

	i = 0;
	curr = tail;
	pthread_mutex_destroy(&curr->mutx_help->mtx_print);
	pthread_mutex_destroy(&curr->mutx_help->mtx_death);
	free(tail->mutx_help);
	tail->mutx_help = NULL;
}
