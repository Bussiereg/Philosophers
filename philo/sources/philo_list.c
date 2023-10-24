/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbussier <gbussier@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 17:03:34 by gbussier          #+#    #+#             */
/*   Updated: 2023/09/21 17:05:13 by gbussier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	insert_end(t_philo **tet, int vl, t_cond arg)
{
	t_philo	*new_node;

	new_node = malloc(sizeof(t_philo));
	if (!new_node)
		return ;
	new_node->philo_nb = vl;
	pthread_mutex_init(&new_node->fork, NULL);
	pthread_mutex_init(&new_node->mtx_stat_fork, NULL);
	new_node->nb_of_meal = 0;
	new_node->stat_fork = 0;
	new_node->mutx_help = (*tet)->mutx_help;
	new_node->next_philo = NULL;
	new_node->last_philo = *tet;
	new_node->arg = arg;
	(*tet)->next_philo = new_node;
	*tet = new_node;
}
