#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct condition_s
{
    int number_of_philosophers;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int number_of_meal;
    long time_init;
} condition_t;

typedef struct philo_s
{
    int                 PhiloNumber;
    int                 nb_of_meal;
    pthread_t           Philosopher;
    pthread_mutex_t     Fork;
    pthread_mutex_t     *lock_print;
    int                 death;
    struct philo_s      *NextPhilo;
    struct philo_s      *LastPhilo;
    condition_t         arguments;
} philo_t;

void    init(philo_t **tail, philo_t **head, int value, condition_t *arguments, pthread_mutex_t *lock_print);
void    insert_end(philo_t   **head, int value, condition_t arguments, pthread_mutex_t *lock_print);
void    insert_beginning(philo_t **tail, int value);
void print_message(philo_t *Philo, char *mess);

// utils.c
void deallocate(philo_t **tail, philo_t **head, int NbPhilo);
int	ft_atoi(const char *str);
size_t	ft_strlen(const char *str);
int	ft_strncmp(const char *s1, const char *s2, size_t n);

// init.c
void    init_table(philo_t **head, philo_t **tail, int NbPhilo, condition_t *arguments, pthread_mutex_t *lock_print);
void    init_args(condition_t *arguments, char **argv, int argc);

#endif