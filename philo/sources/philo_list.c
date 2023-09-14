#include "philosophers.h"

void    insert_beginning(philo_t **tail, int value)
{
    philo_t *new_node;
    
    new_node = malloc(sizeof(philo_t));
    if (!new_node)
        return ;
    new_node->PhiloNumber = value;
    new_node->nb_of_meal = 0;
    new_node->LastPhilo = NULL;
    new_node->NextPhilo = *tail;
    if (*tail != NULL)
    {
        (*tail)->LastPhilo = new_node;
    }
    *tail = new_node;
}

void    insert_end(philo_t   **head, int value, condition_t arguments, pthread_mutex_t *lock_print)
{
    philo_t  *new_node;

    new_node = malloc(sizeof(philo_t));
    if (!new_node)
        return;
    new_node->PhiloNumber = value;
    new_node->lock_print = lock_print;
    new_node->nb_of_meal = 0;
    new_node->NextPhilo = NULL;
    new_node->LastPhilo = *head;
    new_node->arguments = arguments;
    (*head)->NextPhilo = new_node;
    *head = new_node;
}

void	print_list(philo_t *lst)
{
	while (lst)
	{
		printf("valeur est :%d\n", lst->PhiloNumber);
		lst = lst->NextPhilo;
	}
}