#include "philosophers.h"

philo_t	*philo_lstnew(int value, char **argv)
{
	philo_t         *head;
    pthread_mutex_t LeftFork;

	head = (philo_t *)malloc(sizeof(*head));
	if (!head)
		return (NULL);
	head->PhiloNumber = value;
    head->time_to_eat = atoi(argv[2]);
    head->time_to_die = atoi(argv[3]);
    head->time_to_sleep = atoi(argv[4]);
    head->nb_of_meal = atoi(argv[5]);
    head->Fork = LeftFork;
    pthread_mutex_init(&LeftFork, NULL);
	head->NextPhilo = NULL;
    head->LastPhilo = NULL;
	return (head);
}

void	philo_lstadd_back(philo_t **lst, philo_t *new)
{
	philo_t	*tmp;

	if (lst)
	{
		if (*lst == NULL)
			*lst = new;
		else
		{
			tmp = philo_lstlast(*lst);
			tmp->NextPhilo = new;
		}
	}
}

philo_t	*philo_lstlast(philo_t *lst)
{
	if (lst == NULL)
		return (lst);
	while (lst->NextPhilo != NULL)
	{
		lst = lst->NextPhilo;
	}
	return (lst);
}

void	print_list(philo_t *lst)
{
	while (lst)
	{
		printf("valeur est :%d\n", lst->PhiloNumber);
		lst = lst->NextPhilo;
	}
}