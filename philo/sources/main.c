#include "philosophers.h"

int sig = 0;

long gettimestamp(condition_t arguments)
{
    long timestamp;
    struct timeval tv2;

    gettimeofday(&tv2, NULL);

    timestamp = (tv2.tv_sec * 1000) + (tv2.tv_usec / 1000) - arguments.time_init;
    return (timestamp);
}

long    time_since_last_meal(condition_t arguments, long time_start)
{
    long result;

    result = gettimestamp(arguments) - time_start;
    return(result);
}

int eating_function(philo_t *Philo)
{
    if (Philo->PhiloNumber % 2 == 0 || Philo->PhiloNumber == 0)
    {
        pthread_mutex_lock(&Philo->Fork);
        print_message(Philo, "has taken a fork");
        pthread_mutex_lock(&Philo->NextPhilo->Fork);
        print_message(Philo, "has taken a fork");
    }
    else
    {
        pthread_mutex_lock(&Philo->NextPhilo->Fork);
        print_message(Philo, "has taken a fork");
        pthread_mutex_lock(&Philo->Fork);
        print_message(Philo, "has taken a fork");
    }
    print_message(Philo, "is eating");
    return (1);
}

int sleeping_function(philo_t *Philo)
{
    print_message(Philo, "is sleeping");
    usleep(Philo->arguments.time_to_sleep * 1000);
    return (1);
}

int check_death(philo_t *Philo, long last_meal_date)
{
    if (time_since_last_meal(Philo->arguments, last_meal_date) > Philo->arguments.time_to_die)
    {
        print_message(Philo, "died");
        Philo->death = Philo->PhiloNumber;
        return (1);
    }
    return (0);
}

int check_death2(philo_t *Philo)
{
    philo_t *curr;
    int i;

    i = 0;
    curr = Philo;
    while (i < Philo->arguments.number_of_philosophers)
    {
        if (curr->death > 0)
            return (1);
        curr = curr->NextPhilo;
        i++;
    }
    return (0);
}

int check_meal(philo_t *Philo)
{
    philo_t *curr;
    int nb_satiated_philo;
    int i;

    i = 0;
    nb_satiated_philo = 0;
    curr = Philo;
    while (i < curr->arguments.number_of_philosophers)
    {
        if (curr->nb_of_meal >= curr->arguments.number_of_meal)
            nb_satiated_philo++;
        curr = curr->NextPhilo;
        i++;
    }
    if (nb_satiated_philo == Philo->arguments.number_of_philosophers)
        return (1);
    return (0);
}

void print_message(philo_t *Philo, char *mess)
{
    static int die = 0;

    pthread_mutex_lock(Philo->lock_print);
    if (die == 0)
    {
        printf("%ld %d %s\n", gettimestamp(Philo->arguments), Philo->PhiloNumber, mess);
        if (ft_strncmp(mess, "died", ft_strlen(mess)) == 0)
        {
            die = 1;
        }
    }
    pthread_mutex_unlock(Philo->lock_print);
}

void *LifePhilo(void *arg)
{
    philo_t *Philo;
    long    last_meal_date;


    Philo = (philo_t*)arg;
    last_meal_date = gettimestamp(Philo->arguments);
    while (Philo->death == 0)
    {
        print_message(Philo, "is thinking");
        if (check_death(Philo, last_meal_date))
            return ((void*)&(Philo->PhiloNumber));
        eating_function(Philo);
        last_meal_date = gettimestamp(Philo->arguments);
        usleep(Philo->arguments.time_to_eat * 1000);
        Philo->nb_of_meal++;
        pthread_mutex_unlock(&Philo->Fork);
        pthread_mutex_unlock(&Philo->NextPhilo->Fork);
        if (check_death(Philo, last_meal_date))
            return ((void*)&(Philo->PhiloNumber));
        sleeping_function(Philo);
        if (check_death(Philo, last_meal_date))
            return ((void*)&(Philo->PhiloNumber));
    }
    return ((void*)&(Philo->PhiloNumber));
}

int	main(int argc, char **argv)
{
    int i;
    int *res = NULL;
    philo_t *head;
    philo_t *tail;
    philo_t *curr;
    condition_t arguments;
    pthread_mutex_t lock_print;

    pthread_mutex_init(&lock_print, NULL);
    if (argc < 5 || argc > 6)
    {
        printf("1: ./philo\n2: number_of_philosophers\n3: time_to_die\n4: time_to_eat\n5: time_to_sleep\n6: [number_of_times_each_philosophers_must_eat]\n");
        return (0);
    }
    init_args(&arguments, argv, argc);
    init_table(&head, &tail, atoi(argv[1]), &arguments, &lock_print);
    i = 0;
    curr = tail;
    while (i < atoi(argv[1]))
    {
        pthread_mutex_init(&curr->Fork, NULL);
        i++;
        curr = curr->NextPhilo;
    }
    i = 0;
    curr = tail;
    while (i < atoi(argv[1]))
    {
        pthread_create(&(curr)->Philosopher, NULL, &LifePhilo, (void*)curr);
        i++;
        curr = curr->NextPhilo;
    }
    i = 0;
    curr = tail;
    while (1)
    {
        if (check_death2(curr) == 1)
        {
            while (i < atoi(argv[1]))
            {
                if (i + 1 == curr->death)
                    pthread_join(curr->Philosopher, (void**)&res);
                else
                    pthread_detach(curr->Philosopher);
                curr = curr->NextPhilo;
                i++;
            }
            break;
        }
        else if (argc == 6 && check_meal(curr) == 1)
        {
            while (i < atoi(argv[1]))
            {
                pthread_detach(curr->Philosopher);
                curr = curr->NextPhilo;
                i++;
            }
            break;
        }
    }
    i = 0;
    curr = tail;
    while (i < atoi(argv[1]))
    {
        pthread_mutex_destroy(&curr->Fork);
        i++;
        curr = curr->NextPhilo;
    }
    pthread_mutex_destroy(&lock_print);
    deallocate(&tail, &head, atoi(argv[1]));
    return (0);
}