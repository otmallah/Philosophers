#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>


long long     time2(void)
{
		struct  timeval current_time;
		long long time;

		gettimeofday(&current_time, NULL);
		time = (long long)(current_time.tv_sec  + current_time.tv_usec );
		return time;
}

int main()
{
	long long time;

	time = time2();
	printf("time = %lld \n", time);
}
