#include "philo.h"

int x = 0;

void	*fun()
{
	printf("x = %d\n", x);
	x++;
}

int main(int ac, char **av)
{
	t_philo philo;
	pthread_t *philosophers;
	t_list *list;
	int i;

	i = 0;
	list = NULL;
	philosophers = malloc(sizeof(pthread_t) * atoi(av[1]));
	while(i < atoi(av[1]))
	{
		pthread_create(&philosophers[i], NULL, fun, NULL);
		if (i == 0)
			list = ft_lstnew(philosophers[i]);
		i++;
	}
}
