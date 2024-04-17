#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>
#include <stdlib.h>

void *heavy_work(void *arg)
{
	(void) arg;
	volatile int num;

	num = 0;
	for (int i = 0; i < 1000000000; i++)
	{
		num += i;
	}
	printf("%d\n", num);
	return (0);
}

size_t get_time_in_us()
{
	struct timeval	cur;
	gettimeofday(&cur, NULL);
	return (cur.tv_sec * 1000000 + cur.tv_usec);
}

int main()
{
	pthread_t thread[30];
	size_t start = get_time_in_us();
	for (int i = 0; i < 30; i++)
		heavy_work(0);
	start = get_time_in_us() - start;
	printf("time_taken: [%zu]\n", start);
}