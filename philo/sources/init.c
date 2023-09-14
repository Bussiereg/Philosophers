#include "philosophers.h"

void    init(philo_t **tail, philo_t **head, int value, condition_t *arguments, pthread_mutex_t *lock_print)
{
    philo_t *new_node;

    new_node = malloc(sizeof(philo_t));
    if (!new_node)
        return;
    new_node->PhiloNumber = value;
    new_node->lock_print = lock_print;
    new_node->nb_of_meal = 0;
    new_node->death = 0;
    new_node->LastPhilo = NULL;
    new_node->NextPhilo = NULL;
    new_node->arguments = *arguments;
    *tail = new_node;
    *head = new_node;
}

void    init_table(philo_t **head, philo_t **tail, int NbPhilo, condition_t *arguments, pthread_mutex_t *lock_print)
{
    int i;

    i = 2;
    init(tail, head, 1, arguments, lock_print);
    while (i <= NbPhilo)
    {
        insert_end(head, i, *arguments, lock_print);
        i++;
    }
    (*tail)->LastPhilo = *head;
    (*head)->NextPhilo = *tail;

}

void    init_args(condition_t *arguments, char **argv, int argc)
{
    condition_t data_cond;
    struct timeval tv;

    gettimeofday(&tv, NULL);
    data_cond.number_of_philosophers = atoi(argv[1]);
    data_cond.time_to_die = atoi(argv[2]);
    data_cond.time_to_eat = atoi(argv[3]);
    data_cond.time_to_sleep = atoi(argv[4]);
    data_cond.time_init = tv.tv_sec * 1000 + (tv.tv_usec / 1000);
    if (argc == 6)
        data_cond.number_of_meal = atoi(argv[5]);
    else
        data_cond.number_of_meal = -1;
    *arguments = data_cond;
}