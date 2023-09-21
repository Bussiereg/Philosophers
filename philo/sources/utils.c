/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbussier <gbussier@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 17:06:14 by gbussier          #+#    #+#             */
/*   Updated: 2023/09/21 17:06:58 by gbussier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	deallocate(philo_t **tail, philo_t **head, int NbPhilo)
{
	philo_t	*curr;
	int		i;

	i = 1;
	if (*tail == NULL)
		return ;
	curr = *tail;
	while (i < NbPhilo)
	{
		curr = curr->NextPhilo;
		free(curr->LastPhilo);
		i++;
	}
	free(curr);
	*tail = NULL;
	*head = NULL;
}

void	print_message(philo_t *Philo, char *mess, long timestamp)
{
	static int	die = 0;

	pthread_mutex_lock(Philo->lock_print);
	if (die == 0)
	{
		printf("%ld %d %s\n", timestamp, Philo->PhiloNumber, mess);
		if (mess[0] == 'd')
			die = 1;
	}
	pthread_mutex_unlock(Philo->lock_print);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	signe;
	int	result;

	signe = 1;
	result = 0;
	i = 0;
	while ((str[i] == ' ') || (str[i] == '\f') || (str[i] == '\n')
		|| (str[i] == '\r') || (str[i] == '\t') || (str[i] == '\v'))
	{
		i++;
	}
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			signe = signe * (-1);
		i++;
	}
	while ((str[i] >= '0') && (str[i] <= '9'))
	{
		result = (result * 10) + (str[i] - 48);
		i++;
	}
	return (result * signe);
}

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;
	unsigned char	*str1;
	unsigned char	*str2;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	i = 0;
	if (n == 0)
		return (0);
	while ((i <= n - 1) && (i <= ft_strlen(s1)))
	{
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
		else
			i++;
	}
	return (0);
}
