/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobroue <lobroue@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/25 11:22:36 by lobroue           #+#    #+#             */
/*   Updated: 2026/08/04 01:27:18 by lobroue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	heap_push(t_heap *heap, t_request req)
{
	heap->data[heap->size] = req;
	heap->size++;
	heap_sift_up(heap, heap->size - 1);
}
t_request	heap_pop(t_heap *heap)
{
	t_request	top;

	top = heap->data[0];
	heap->size--;
	heap->data[0] = heap->data[heap->size];
	heap_sift_down(heap, 0);
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