#include "philosophers.h"

int	main(int argc, char **argv)
{
    if (argc < 5 || argc > 6)
    {
        printf("1: ./philo\n2: number_of_philosophers\n3: time_to_die\n4: time_to_eat\n5: time_to_sleep\n6: [number_of_times_each_philosophers_must_eat]\n");
        return (0);
    }
    printf("hello world of philosophers! le nom du programme est: \n%s\n", argv[0]);
    return (0);
}
