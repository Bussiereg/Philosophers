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

int	check_sleep(t_philo *philo, long last_meal_date, char *activity)
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
			philo->death = philo->philo_nb;
			return (1);
		}
	}
	return (0);
}

int	check_death(t_philo *philo, long lastmeal, char *activity)
{
	if (check_sleep(philo, lastmeal, activity) == 1)
		return (1);
	else if (ft_strncmp(activity, "eat", ft_strlen(activity)) == 0)
	{
		if (time_since_last_meal(philo->arg, lastmeal) 
			+ philo->arg.time_to_eat > philo->arg.time_to_die)
		{
			usleep((philo->arg.time_to_die
					- time_since_last_meal(philo->arg, lastmeal)) * 1000);
			print_message(philo, "died", gettimestamp(philo->arg));
			philo->death = philo->philo_nb;
			return (1);
		}
	}
	else if (ft_strncmp(activity, "death", ft_strlen(activity)) == 0)
	{
		if (time_since_last_meal(philo->arg, lastmeal) > philo->arg.time_to_die)
		{
			print_message(philo, "died", gettimestamp(philo->arg));
			philo->death = philo->philo_nb;
			return (1);
		}
	}
	return (0);
}

int	check_death_table(t_philo *philo, t_cond argument)
{
	t_philo	*curr;
	int		i;

	i = 0;
	curr = philo;
	while (i < philo->arg.number_of_philosophers)
	{
		if (curr->death > 0)
		{
			while (i < argument.number_of_philosophers)
			{
				if (i + 1 == curr->death)
					pthread_join(curr->philosopher, NULL);
				else
					pthread_detach(curr->philosopher);
				curr = curr->next_philo;
				i++;
			}
			return (1);
		}
		curr = curr->next_philo;
		i++;
	}
	return (0);
}

int	check_meal(t_philo *philo, t_cond argument, int i, int j)
{
	t_philo	*curr;

	curr = philo;
	if (argument.argc != 6)
		return (0);
	while (i++ < curr->arg.number_of_philosophers)
	{
		if (curr->nb_of_meal >= curr->arg.number_of_meal)
			j++;
		curr = curr->next_philo;
	}
	if (j == philo->arg.number_of_philosophers)
	{
		while (i++ < argument.number_of_philosophers)
		{
			pthread_detach(curr->philosopher);
			curr = curr->next_philo;
		}
		return (1);
	}
	return (0);
}

int	check_input( int argc, char **argv)
{
	if (argc < 5 || argc > 6)
	{
		printf("1: ./philo\n2: number_of_philosophers\n3: time_to_die\n");
		printf("4: time_to_eat\n5: time_to_sleep\n");
		printf("6: [number_of_times_each_philosophers_must_eat]\n");
		return (0);
	}
	if (ft_atoi(argv[1]) <= 0)
		return (0);
	return (1);
}
