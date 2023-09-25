/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbussier <gbussier@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 17:05:28 by gbussier          #+#    #+#             */
/*   Updated: 2023/09/21 17:06:03 by gbussier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

long	gettimestamp(t_cond arg)
{
	long			timestamp;
	struct timeval	tv2;

	gettimeofday(&tv2, NULL);
	timestamp = (tv2.tv_sec * 1000) + (tv2.tv_usec / 1000) - arg.time_init;
	return (timestamp);
}

long	time_since_last_meal(t_cond arg, long time_start)
{
	long	result;

	result = gettimestamp(arg) - time_start;
	return (result);
}
