
#include <sys/time.h>
#include <stdio.h>
#include <pthread.h>

int array[10] = {10, 22, 5, 8, 45, 75, 84, 89, 2, 15};
int x;
pthread_mutex_t mutex;

void	*fun0(void	*num)
{
	for(int i = 0; i < 10000; i++)
	{
		pthread_mutex_lock(&mutex);
		x++;
		pthread_mutex_unlock(&mutex);
	}
}

int main(int ac, char **av)
{
	pthread_t t1[10];

	pthread_mutex_init(&mutex, NULL);
	for (int i = 0; i < 10; i++) {
		pthread_create(&t1[i], NULL, fun0, &i);
		// pthread_detach(t1[i]);
	}
	for (int i = 0; i < 10; i++ )
	{
		pthread_join(t1[i], NULL);
	}
	printf("%d \n", x);
	pthread_mutex_destroy(&mutex);
}
 