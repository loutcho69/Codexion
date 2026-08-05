/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobroue <lobroue@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/05 18:15:09 by lobroue           #+#    #+#             */
/*   Updated: 2026/08/05 18:26:05 by lobroue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	heap_remove_by_id(t_heap *heap, int coder_id)
{
	int	i;

	i = 0;
	while (i < heap->size && heap->data[i].coder_id != coder_id)
		i++;
	if (i == heap->size)
		return ;
	heap->size--;
	heap->data[i] = heap->data[heap->size];
	heap_sift_down(heap, i);
	heap_sift_up(heap, i);
}

void	heap_sift_up(t_heap *heap, int i)
{
	while (i > 0 && heap->data[i].key < heap->data[heap_parent(i)].key)
	{
		heap_swap(&heap->data[i], &heap->data[heap_parent(i)]);
		i = heap_parent(i);
	}
}

void	heap_sift_down(t_heap *heap, int i)
{
	int	smallest;

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
}
