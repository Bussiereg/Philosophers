/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbussier <gbussier@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 17:37:12 by gbussier          #+#    #+#             */
/*   Updated: 2023/09/22 19:01:53 by gbussier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_condition
{
	int		number_of_philosophers;
	time_t	time_to_die;
	time_t	time_to_eat;
	time_t	time_to_sleep;
	int		number_of_meal;
	int		argc;
	time_t	time_init;
}	t_cond;

typedef struct s_philo
{
	int					philo_nb;
	int					nb_of_meal;
	pthread_t			philosopher;
	pthread_mutex_t		*lock_print;
	pthread_mutex_t		fork;
	int					fork_tatus;
	int					death;
	struct s_philo		*next_philo;
	struct s_philo		*last_philo;
	t_cond				arg;
}	t_philo;

// philo_list.c
void	insert_end(t_philo **tet, int vl, t_cond arg, pthread_mutex_t *lp);
void	insert_beginning(t_philo **tail, int value);

// utils.c
void	deallocate(t_philo **tail, t_philo **head, int philo_nb);
int		ft_atoi(const char *str);
void	print_message(t_philo *Philo, char *mess, long timestamp);
size_t	ft_strlen(const char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

// init.c
void	init_table(t_philo **hd, t_philo **tl, t_cond *ag, pthread_mutex_t *lp);
void	init_args(t_cond *arg, char **argv, int argc);
void	init(t_philo **tl, t_philo **hd, t_cond *arg, pthread_mutex_t *lp);
int		init_lifephilo(t_philo *philo, long *last_meal_date);

// action.c
int		sleeping_function(t_philo *philo, long *last_meal_date);
int		eating_function(t_philo *philo, long *last_meal_date);
int		thinking_function(t_philo *philo, long *last_meal_date, int *flag);

// time.c
long	gettimestamp(t_cond arg);
long	time_since_last_meal(t_cond arg, long time_start);

// main.c
void	*single_philo(t_philo *philo);
void	*lifephilo(void *arg);
void	close_simulation(t_philo *tail, t_cond argument);
void	init_simulation(t_philo *tail, char **argv);

// check.c
int		check_death(t_philo *philo, long last_meal_date, char *activity);
int		check_death_table(t_philo *philo, t_cond argument);
int		check_meal(t_philo *philo, t_cond argument, int i, int j);
int		check_input( int argc, char **argv);

#endif
