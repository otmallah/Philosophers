#include <stdio.h>

int main(int ac, char **av)
{
    int id;
    int a = 0;

    id = fork();
    if (id == 0)
        a += 5;
    printf("a = %d\n" , a);
    return 0;
}