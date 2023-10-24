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

void	deallocate(t_philo **tail, t_philo **head, int philo_nb)
{
	t_philo	*curr;
	int		i;

	i = 1;
	if (*tail == NULL)
		return ;
	curr = *tail;
	while (i < philo_nb)
	{
		curr = curr->next_philo;
		pthread_mutex_destroy(&curr->last_philo->fork);
		pthread_mutex_destroy(&curr->last_philo->mtx_stat_fork);
		free(curr->last_philo);
		curr->last_philo = NULL;
		i++;
	}
	pthread_mutex_destroy(&curr->fork);
	pthread_mutex_destroy(&curr->mtx_stat_fork);
	free(curr);
	curr = NULL;
	*tail = NULL;
	*head = NULL;
}

void	print_message(t_philo *philo, char *mess, long timestamp)
{
	pthread_mutex_lock(&(philo->mutx_help->mtx_print));
	if (philo->mutx_help->stat_print == 0)
	{
		printf("%ld %d %s\n", timestamp, philo->philo_nb, mess);
		if (mess[0] == 'd')
			philo->mutx_help->stat_print = 1;
	}
	pthread_mutex_unlock(&(philo->mutx_help->mtx_print));
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
