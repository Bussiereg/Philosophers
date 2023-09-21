/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbussier <gbussier@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 17:00:08 by gbussier          #+#    #+#             */
/*   Updated: 2023/09/21 17:00:59 by gbussier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

int	check_death(philo_t *Philo, long last_meal_date, char *activity)
{
	long	temp;

	temp = 0;
	if (ft_strncmp(activity, "sleep", ft_strlen(activity)) == 0)
	{
		temp = time_since_last_meal(Philo->arguments, last_meal_date) + Philo->arguments.time_to_sleep;
		if (temp > Philo->arguments.time_to_die)
		{
			print_message(Philo, "is sleeping", gettimestamp(Philo->arguments));
			usleep((Philo->arguments.time_to_die - Philo->arguments.time_to_sleep) * 1000);
			print_message(Philo, "died", gettimestamp(Philo->arguments));
			Philo->death = Philo->PhiloNumber;
			return (1);
		}
	}
	else if (ft_strncmp(activity, "death", ft_strlen(activity)) == 0)
	{
		temp = time_since_last_meal(Philo->arguments, last_meal_date);
		if (temp > Philo->arguments.time_to_die)
		{
			print_message(Philo, "died", gettimestamp(Philo->arguments));
			Philo->death = Philo->PhiloNumber;
			return (1);
		}
	}
	return (0);
}

int	check_death2(philo_t *Philo)
{
	philo_t	*curr;
	int		i;

	i = 0;
	curr = Philo;
	while (i < Philo->arguments.number_of_philosophers)
	{
		if (curr->death > 0)
			return (1);
		curr = curr->NextPhilo;
		i++;
	}
	return (0);
}

int	check_meal(philo_t *Philo)
{
	philo_t	*curr;
	int		nb_satiated_philo;
	int		i;

	i = 0;
	nb_satiated_philo = 0;
	curr = Philo;
	while (i < curr->arguments.number_of_philosophers)
	{
		if (curr->nb_of_meal >= curr->arguments.number_of_meal)
			nb_satiated_philo++;
		curr = curr->NextPhilo;
		i++;
	}
	if (nb_satiated_philo == Philo->arguments.number_of_philosophers)
		return (1);
	return (0);
}
