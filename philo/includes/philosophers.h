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
    pthread_mutex_t     *lock_print;
    pthread_mutex_t     Fork;
    int                 ForkStatus;
    int                 death;
    struct philo_s      *NextPhilo;
    struct philo_s      *LastPhilo;
    condition_t         arguments;
} philo_t;

void    init(philo_t **tail, philo_t **head, int value, condition_t *arguments, pthread_mutex_t *lock_print);
void    insert_end(philo_t   **head, int value, condition_t arguments, pthread_mutex_t *lock_print);
void    insert_beginning(philo_t **tail, int value);
void print_message(philo_t *Philo, char *mess, long timestamp);

// utils.c
void deallocate(philo_t **tail, philo_t **head, int NbPhilo);
int	ft_atoi(const char *str);
size_t	ft_strlen(const char *str);
int	ft_strncmp(const char *s1, const char *s2, size_t n);

// init.c
void    init_table(philo_t **head, philo_t **tail, int NbPhilo, condition_t *arguments, pthread_mutex_t *lock_print);
void    init_args(condition_t *arguments, char **argv, int argc);


// action.c
int sleeping_function(philo_t *Philo);
int eating_function(philo_t *Philo);

// time.c
long gettimestamp(condition_t arguments);
long    time_since_last_meal(condition_t arguments, long time_start);

// main.c
int check_death(philo_t *Philo, long last_meal_date, char *activity);

// check.c
int check_death(philo_t *Philo, long last_meal_date, char *activity);
int check_death2(philo_t *Philo);
int check_meal(philo_t *Philo);

#endif