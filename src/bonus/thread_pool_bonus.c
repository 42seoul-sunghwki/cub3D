/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_pool_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 18:09:16 by minsepar          #+#    #+#             */
/*   Updated: 2024/04/21 16:09:35 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/**
 * worker routine function
 * t_task will be freed after task is done
*/
static void	*worker_thread(void *arg)
{
	t_thread_pool	*pool;
	t_task			*task;

	pool = arg;
	while (1)
	{
		pthread_mutex_lock(&pool->mutex);
		while (pool->queue.size == 0 && !pool->shutdown)
			pthread_cond_wait(&pool->condition, &pool->mutex);
		if (pool->shutdown)
		{
			pthread_mutex_unlock(&pool->mutex);
			pthread_exit(NULL);
		}
		task = pop_task(pool);
		pthread_mutex_unlock(&pool->mutex);
		task->function(task->arg);
		pthread_mutex_lock(&pool->mutex);
		pool->task_complete++;
		// printf("task complete: %d\n", pool->task_complete);
		pthread_cond_signal(&pool->synchronize);
		pthread_mutex_unlock(&pool->mutex);
		free(task);
	}
}

void	thread_pool_init(t_thread_pool *pool, int num_threads)
{
	int	i;

	pool->num_threads = num_threads;
	pool->queue.size = 0;
	pool->shutdown = false;
	pool->threads = malloc(sizeof(pthread_t) * num_threads);
	pthread_mutex_init(&pool->mutex, NULL);
	pthread_cond_init(&pool->condition, NULL);
	pthread_cond_init(&pool->synchronize, NULL);
	i = -1;
	while (++i < num_threads)
	{
		pthread_create(&pool->threads[i], NULL, worker_thread, (void *)pool);
	}
}

void	thread_pool_shutdown(t_thread_pool *pool)
{
	int	i;

	i = -1;
	pthread_mutex_lock(&pool->mutex);
	pool->shutdown = true;
	pthread_mutex_unlock(&pool->mutex);
	pthread_cond_broadcast(&pool->condition);
	while (++i < pool->num_threads)
		pthread_join(pool->threads[i], NULL);
	pthread_join(pool->threads[i], NULL);
	pthread_mutex_destroy(&pool->mutex);
	pthread_cond_destroy(&pool->condition);
}

void	start_wait_for_threads(t_thread_pool *pool, int total_task)
{
	pthread_mutex_lock(&pool->mutex);
	pool->total_task = total_task;
	pool->task_complete = 0;
	pthread_mutex_unlock(&pool->mutex);
}

void	wait_for_threads(t_thread_pool *pool)
{
	// printf("%d\n", pool->total_task);
	pthread_mutex_lock(&pool->mutex);
	while (pool->task_complete < pool->total_task)
	{
		pthread_cond_wait(&pool->synchronize, &pool->mutex);
	}
	pthread_mutex_unlock(&pool->mutex);
}
