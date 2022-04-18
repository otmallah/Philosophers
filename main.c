
#include <sys/time.h>
#include <stdio.h>
#include <pthread.h>

int array[10] = {10, 22, 5, 8, 45, 75, 84, 89, 2, 15};

void	*fun0(void	*num)
{
	sleep(1);
	printf("finesh hh\n");
}

int main(int ac, char **av)
{
	pthread_t t1[10];

	for (int i = 0; i < 10; i++) {
		pthread_create(&t1[i], NULL, fun0, &i);
		pthread_detach(t1[i]);
	}
	for (int i = 0; i < 10; i++)
	{
		if ( pthread_join(t1[i], NULL) != 0)
			printf("faild to join hh\n");
	}
}
