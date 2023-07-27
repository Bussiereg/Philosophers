#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct philo_s
{
    int             PhiloNumber;
    int             time_to_eat;
    int             time_to_die;
    int             time_to_sleep;
    int             nb_of_meal;
    pthread_mutex_t Fork;
    struct philo_s  *NextPhilo;
    struct philo_s  *LastPhilo;
} philo_t;


philo_t *philo_lstnew(int value, char **argv);
void    philo_lstadd_back(philo_t **lst, philo_t *new);
philo_t *philo_lstlast(philo_t *lst);



#endif