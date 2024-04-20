/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_pool_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 18:09:16 by minsepar          #+#    #+#             */
/*   Updated: 2024/04/20 19:08:26 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

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
