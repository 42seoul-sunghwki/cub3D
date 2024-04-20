#ifndef TEST_H
#define TEST_H

#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>


typedef struct s_task
{
	void			(*function)(void *);
	void			*arg;
	struct s_task	*next;
	struct s_task	*prev;
}	t_task;

typedef struct s_task_queue
{
	t_task	*head;
	t_task	*tail;
	int		size;
}	t_task_queue;

typedef struct s_thread_pool
{
	pthread_t		*threads;
	t_task_queue	queue;
	int				num_threads;
	pthread_mutex_t	mutex;
	pthread_cond_t	condition;
	bool			shutdown;
}	t_thread_pool;

t_task	*pop_task(t_thread_pool *pool);
void	add_task(t_thread_pool *pool, t_task *task);
t_task	*create_task(void (*function)(void *), void *arg);
void	thread_pool_init(t_thread_pool *pool, int num_threads);
void	thread_pool_shutdown(t_thread_pool *pool);
static void	*worker_thread(void *arg);

#endif