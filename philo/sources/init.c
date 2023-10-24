/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbussier <gbussier@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 17:01:24 by gbussier          #+#    #+#             */
/*   Updated: 2023/09/21 17:02:21 by gbussier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_mtx(t_mutex *mtxhelp)
{
	pthread_mutex_init(&mtxhelp->mtx_print, NULL);
	pthread_mutex_init(&mtxhelp->mtx_death, NULL);
	pthread_mutex_init(&mtxhelp->mtx_meal, NULL);
	mtxhelp->stat_death = 0;
	mtxhelp->stat_print = 0;
	mtxhelp->count_meal = 0;
}

void	init(t_philo **tl, t_philo **hd, t_cond *arg)
{
	t_philo	*new_node;
	t_mutex	*mtxhelp;

	mtxhelp = malloc(sizeof(t_mutex));
	if (!mtxhelp)
		return ;
	init_mtx(mtxhelp);
	new_node = malloc(sizeof(t_philo));
	if (!new_node)
		return ;
	pthread_mutex_init(&new_node->fork, NULL);
	pthread_mutex_init(&new_node->mtx_stat_fork, NULL);
	new_node->philo_nb = 1;
	new_node->nb_of_meal = 0;
	new_node->mutx_help = mtxhelp;
	new_node->stat_fork = 0;
	new_node->last_philo = NULL;
	new_node->next_philo = NULL;
	new_node->arg = *arg;
	*tl = new_node;
	*hd = new_node;
}

void	init_table(t_philo **hd, t_philo **tl, t_cond *ag)
{
	int	i;

	i = 2;
	init(tl, hd, ag);
	while (i <= ag->number_of_philosophers)
	{
		insert_end(hd, i, *ag);
		i++;
	}
	(*tl)->last_philo = *hd;
	(*hd)->next_philo = *tl;
}

void	init_args(t_cond *arg, char **argv, int argc)
{
	t_cond			data_cond;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	data_cond.number_of_philosophers = atoi(argv[1]);
	data_cond.time_to_die = atoi(argv[2]);
	data_cond.time_to_eat = atoi(argv[3]);
	data_cond.time_to_sleep = atoi(argv[4]);
	data_cond.argc = argc;
	data_cond.time_init = tv.tv_sec * 1000 + (tv.tv_usec / 1000) + 1000;
	if (argc == 6)
		data_cond.number_of_meal = atoi(argv[5]);
	else
		data_cond.number_of_meal = -1;
	*arg = data_cond;
}

int	init_lifephilo(t_philo *philo, long *last_meal_date)
{
	if (philo->arg.number_of_philosophers == 1)
	{
		single_philo(philo);
		return (0);
	}
	while (gettimestamp(philo->arg) < 0)
		usleep(500);
	*last_meal_date = gettimestamp(philo->arg);
	return (1);
}
