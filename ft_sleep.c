#include "philo.h"

void    ft_sleep(int num)
{
    int a;

    a = 1;
    while (a <= num)
    {
        printf("a == %d\n" , a);
        usleep(a * 1000);
        a++;
    }
}

int main(int ac, char **av)
{
    ft_sleep(atoi(av[1]));
}