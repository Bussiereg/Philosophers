/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbussier <gbussier@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 17:07:12 by gbussier          #+#    #+#             */
/*   Updated: 2023/09/21 17:09:35 by gbussier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	single_philo(philo_t *Philo)
{
	while (gettimestamp(Philo->arguments) < 0)
	{
		usleep(500);
	}
	printf("%ld %d is thinking\n", gettimestamp(Philo->arguments), 1);
	printf("%ld %d has taken a fork\n", gettimestamp(Philo->arguments), 1);
	usleep(Philo->arguments.time_to_die * 1000);
	print_message(Philo, "died", gettimestamp(Philo->arguments));
	Philo->death = Philo->PhiloNumber;
	return (1);
}

void	*lifephilo(void *arg)
{
	philo_t	*Philo;
	long	last_meal_date;
	int		flag;

	flag = 0;
	Philo = (philo_t *)arg;
	if (Philo->arguments.number_of_philosophers == 1)
	{
		single_philo(Philo);
		return (NULL);
	}
	while (gettimestamp(Philo->arguments) < 0)
	{
		usleep(500);
	}
	last_meal_date = gettimestamp(Philo->arguments);
	while (Philo->death == 0)
	{
		print_message(Philo, "is thinking", gettimestamp(Philo->arguments));
		if (flag == 1)
			usleep(1000);
		else if (flag == 0 && Philo->PhiloNumber % 2)
		{
			usleep(1000);
			flag = 1;
		}
		while ((Philo->ForkStatus + Philo->NextPhilo->ForkStatus) != 0)
		{
			if (check_death(Philo, last_meal_date, "death"))
				return ((void *)&(Philo->PhiloNumber));
			usleep(100);
		}
		eating_function(Philo);
		print_message(Philo, "is eating", gettimestamp(Philo->arguments));
		last_meal_date = gettimestamp(Philo->arguments);
		Philo->nb_of_meal++;
		usleep(Philo->arguments.time_to_eat * 1000);
		if (check_death(Philo, last_meal_date, "death"))
			return ((void *)&(Philo->PhiloNumber));
		Philo->ForkStatus = 0;
		pthread_mutex_unlock(&Philo->Fork);
		Philo->NextPhilo->ForkStatus = 0;
		pthread_mutex_unlock(&Philo->NextPhilo->Fork);
		if (check_death(Philo, last_meal_date, "sleep"))
			return ((void *)&(Philo->PhiloNumber));
		sleeping_function(Philo);
		if (check_death(Philo, last_meal_date, "death"))
			return ((void *)&(Philo->PhiloNumber));
	}
	return ((void *)&(Philo->PhiloNumber));
}

int	main(int argc, char **argv)
{
	int				i;
	philo_t			*head;
	philo_t			*tail;
	philo_t			*curr;
	condition_t		arguments;
	pthread_mutex_t	lock_print;

	pthread_mutex_init(&lock_print, NULL);
	if (argc < 5 || argc > 6)
	{
		printf("1: ./philo\n2: number_of_philosophers\n3: time_to_die\n4: time_to_eat\n5: time_to_sleep\n6: [number_of_times_each_philosophers_must_eat]\n");
		return (0);
	}
	init_args(&arguments, argv, argc);
	init_table(&head, &tail, atoi(argv[1]), &arguments, &lock_print);
	i = 0;
	curr = tail;
	while (i < atoi(argv[1]))
	{
		pthread_mutex_init(&curr->Fork, NULL);
		i++;
		curr = curr->NextPhilo;
	}
	i = 0;
	curr = tail;
	while (i < atoi(argv[1]))
	{
		pthread_create(&(curr)->Philosopher, NULL, &lifephilo, (void *)curr);
		i++;
		curr = curr->NextPhilo;
	}
	i = 0;
	curr = tail;
	while (1)
	{
		if (check_death2(curr) == 1)
		{
			while (i < atoi(argv[1]))
			{
				if (i + 1 == curr->death)
					pthread_join(curr->Philosopher, NULL);
				else
					pthread_detach(curr->Philosopher);
				curr = curr->NextPhilo;
				i++;
			}
			break ;
		}
		else if (argc == 6 && check_meal(curr) == 1)
		{
			while (i < atoi(argv[1]))
			{
				pthread_detach(curr->Philosopher);
				curr = curr->NextPhilo;
				i++;
			}
			break ;
		}
	}
	usleep(10000);
	i = 0;
	curr = tail;
	while (i < atoi(argv[1]))
	{
		pthread_mutex_destroy(&curr->Fork);
		i++;
		curr = curr->NextPhilo;
	}
	pthread_mutex_destroy(&lock_print);
	deallocate(&tail, &head, atoi(argv[1]));
	return (0);
}
