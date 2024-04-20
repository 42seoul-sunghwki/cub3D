#include "test.h"
#include <stdio.h>
#include <unistd.h>

void	print_hi(void *arg)
{
	printf("hi\n");
}

int main()
{
	t_thread_pool pool;
	int num_tasks = 100;

	thread_pool_init(&pool, 12);

	for (int i = 0; i < num_tasks; ++i)
	{
		int *task_num = malloc(sizeof(int));
		*task_num = i;
		add_task(&pool, create_task(print_hi, NULL));
	}
	for (int i = 0; i < 5; i++)
	{
		sleep(1);
		printf("sec: %d\n", i);
	}
	thread_pool_shutdown(&pool);
}
