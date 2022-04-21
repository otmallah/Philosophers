#include "philo.h"

void    ft_sleep(int num)
{
    int i;
    int a;

    a = num / 5;
    while (a <= num)
    {
        printf("%d \n", a);
        usleep(a * 1000);
        a += (num / 3);
    }
}

int main(int ac, char **av)
{
    ft_sleep(atoi(av[1]));
}