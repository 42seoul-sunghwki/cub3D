/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   task_queue_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 18:10:01 by minsepar          #+#    #+#             */
/*   Updated: 2024/04/20 21:35:56 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

t_task	*create_task(void (*function)(void *), void *arg)
{
	t_task	*return_task;

	return_task = malloc(sizeof(t_task));
	return_task->function = function;
	return_task->arg = arg;
	return (return_task);
}

void	add_task(t_thread_pool *pool, t_task *task)
{
	t_task_queue	*queue;

	queue = &pool->queue;
	pthread_mutex_lock(&pool->mutex);
	if (queue->size == 0)
	{
		queue->head = task;
		queue->tail = task;
	}
	else
	{
		queue->head->prev = task;
		task->next = queue->head;
		queue->head = task;
	}
	pthread_cond_signal(&pool->condition);
	pool->queue.size++;
	pthread_mutex_unlock(&pool->mutex);
}

t_task	*pop_task(t_thread_pool *pool)
{
	t_task_queue	*queue;
	t_task			*return_task;

	queue = &pool->queue;
	return_task = queue->tail;
	if (queue->size == 0)
		return (NULL);
	else if (queue->size == 1)
	{
		queue->head = NULL;
		queue->tail = NULL;
	}
	else
	{
		queue->tail = return_task->prev;
		return_task->prev->next = NULL;
	}
	queue->size--;
	return (return_task);
}
