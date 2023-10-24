/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbussier <gbussier@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 17:07:12 by gbussier          #+#    #+#             */
/*   Updated: 2023/09/22 18:21:32 by gbussier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*single_philo(t_philo *philo)
{
	while (gettimestamp(philo->arg) < 0)
		usleep(500);
	printf("%ld %d is thinking\n", gettimestamp(philo->arg), 1);
	printf("%ld %d has taken a fork\n", gettimestamp(philo->arg), 1);
	usleep(philo->arg.time_to_die * 1000);
	print_message(philo, "died", gettimestamp(philo->arg));
	pthread_mutex_lock(&philo->mutx_help->mtx_death);
	philo->mutx_help->stat_death = philo->philo_nb;
	pthread_mutex_unlock(&philo->mutx_help->mtx_death);
	return (NULL);
}

void	*lifephilo(void *arg)
{
	t_philo	*philo;
	long	last_meal_date;
	int		flag;

	flag = 0;
	philo = (t_philo *)arg;
	if (!init_lifephilo(philo, &last_meal_date))
		return (NULL);
	while (1)
	{
		if (!thinking_function(philo, &last_meal_date, &flag))
			return (NULL);
		if (!eating_function(philo, &last_meal_date))
			return (NULL);
		if (!sleeping_function(philo, &last_meal_date))
			return (NULL);
	}
	return (NULL);
}

void	init_simulation(t_philo *tail, char **argv)
{
	t_philo	*curr;
	int		i;

	i = 0;
	curr = tail;
	while (i < atoi(argv[1]))
	{
		pthread_create(&(curr)->philosopher, NULL, &lifephilo, (void *)curr);
		curr = curr->next_philo;
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_philo			*head;
	t_philo			*tail;
	t_cond			arg;

	if (check_input(argc, argv) == 0)
		return (0);
	init_args(&arg, argv, argc);
	init_table(&head, &tail, &arg);
	init_simulation(tail, argv);
	monitor(tail, arg);
	thread_join(tail);
	close_simulation(tail, arg);
	deallocate(&tail, &head, arg.number_of_philosophers);
	return (1);
}
