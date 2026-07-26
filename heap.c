/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobroue <lobroue@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/25 11:22:36 by lobroue           #+#    #+#             */
/*   Updated: 2026/07/26 19:47:57 by lobroue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	heap_push(t_heap *heap, t_request req)
{
	int	i;

	heap->data[heap->size] = req;
	i = heap->size;
	heap->size++;
	while (i > 0 && heap->data[i].key < heap->data[heap_parent(i)].key)
	{
		heap_swap(&heap->data[i], &heap->data[heap_parent(i)]);
		i = heap_parent(i);
	}
}
t_request	heap_pop(t_heap *heap)
{
	t_request	top;
	int			i;
	int			smallest;

	top = heap->data[0];
	heap->size--;
	heap->data[0] = heap->data[heap->size];
	i = 0;
	while (1)
	{
		smallest = i;
		if (heap_left(i) < heap->size
			&& heap->data[heap_left(i)].key < heap->data[smallest].key)
			smallest = heap_left(i);
		if (heap_right(i) < heap->size
			&& heap->data[heap_right(i)].key < heap->data[smallest].key)
			smallest = heap_right(i);
		if (smallest == i)
			break ;
		heap_swap(&heap->data[i], &heap->data[smallest]);
		i = smallest;
	}
	return (top);
}

t_request	heap_peek(t_heap *heap)
{
	return (heap->data[0]);
}

long	next_seq(t_table *table)
{
	long	seq;

	pthread_mutex_lock(&table->seq_mutex);
	seq = table->seq_counter;
	table->seq_counter++;
	pthread_mutex_unlock(&table->seq_mutex);
	return (seq);
}

long	compute_key(t_coder *coder)
{
	if (coder->table->params.scheduler == 1)
		return (next_seq(coder->table));
	else 
		return (get_last_compil(coder) + coder->table->params.time_to_burnout);
}