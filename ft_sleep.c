#include "philo.h"

void    ft_sleep(int num)
{
    long time;

    time = get_current_time() + num;
    while (get_current_time() <= time)
        usleep(100);
}

int main(int ac, char **av)
{
    ft_sleep(atoi(av[1]));
}