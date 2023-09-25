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

void	insert_beginning(t_philo **tail, int value)
{
	t_philo	*new_node;

	new_node = malloc(sizeof(t_philo));
	if (!new_node)
		return ;
	new_node->philo_nb = value;
	new_node->nb_of_meal = 0;
	new_node->last_philo = NULL;
	new_node->next_philo = *tail;
	if (*tail != NULL)
	{
		(*tail)->last_philo = new_node;
	}
	*tail = new_node;
}

void	insert_end(t_philo **tet, int vl, t_cond arg, pthread_mutex_t *lp)
{
	t_philo	*new_node;

	new_node = malloc(sizeof(t_philo));
	if (!new_node)
		return ;
	new_node->philo_nb = vl;
	new_node->lock_print = lp;
	new_node->nb_of_meal = 0;
	new_node->fork_tatus = 0;
	new_node->next_philo = NULL;
	new_node->last_philo = *tet;
	new_node->arg = arg;
	(*tet)->next_philo = new_node;
	*tet = new_node;
}
