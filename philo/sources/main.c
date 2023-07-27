#include "philosophers.h"


void *LifePhilo(void *arg)
{
    philo_t *Philoarg;

    Philoarg = (philo_t*)arg;
    
    // eat_function
    // sleep_function
    // think_function
    printf("numero du philosophers est: %d\n", Philoarg->PhiloNumber);
    return (NULL);
}


void    Table_init(int NumberOfPhilosophers, philo_t **Table, char **argv)
{
    int i = 0;
    philo_t *temp = NULL;

    while (i < NumberOfPhilosophers)
    {
        temp = philo_lstnew(i, argv);
		philo_lstadd_back(Table, temp);
        i++;
    }
    temp = philo_lstlast(*Table);
    temp->NextPhilo = *Table;
}


int	main(int argc, char **argv)
{
    int i = 0;
    pthread_t *Philosophers;
    philo_t **Table = NULL;
    philo_t *curr;


    if (argc < 5 || argc > 6)
    {
        printf("1: ./philo\n2: number_of_philosophers\n3: time_to_die\n4: time_to_eat\n5: time_to_sleep\n6: [number_of_times_each_philosophers_must_eat]\n");
        return (0);
    }
    Philosophers = malloc(sizeof(Philosophers) * atoi(argv[1]));
    Table_init(atoi(argv[1]), Table, argv);
    curr = *Table;
    i = 0;
    while (i < atoi(argv[1]))
    {
        pthread_create(&Philosophers[i], NULL, &LifePhilo, (void*)curr);
        i++;
        curr = curr->NextPhilo;
    }
    i = 0;
    while (i < atoi(argv[1]))
    {
        pthread_join(Philosophers[i], NULL);
        i++;
    }
    i = 0;
    curr = *Table;
    while (i < atoi(argv[1]))
    {
        pthread_mutex_destroy(&curr->Fork);
        i++;
        curr = curr->NextPhilo;
    }

    return (0);
}



// void *thread_function(void *arg) {
//     pthread_mutex_t *my_mutex = (pthread_mutex_t*)arg;

//     pthread_mutex_lock(my_mutex);

//     printf("had access to memory\n");

//     pthread_mutex_unlock(my_mutex);
//     pthread_exit(NULL);
// }

// int main() {
//     pthread_t thread1, thread2;
//     pthread_mutex_t my_mutex;


//     pthread_mutex_init(&my_mutex, NULL);

//     pthread_create(&thread1, NULL, thread_function, (void*)&my_mutex);
//     pthread_create(&thread2, NULL, thread_function, (void*)&my_mutex);

//     // Attente de la fin des threads
//     pthread_join(thread1, NULL);
//     pthread_join(thread2, NULL);

//     pthread_mutex_destroy(&my_mutex);

//     return 0;
// }
