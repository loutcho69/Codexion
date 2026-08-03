/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobroue <lobroue@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/26 19:46:15 by lobroue           #+#    #+#             */
/*   Updated: 2026/08/04 01:26:24 by lobroue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	heap_swap(t_request *a, t_request *b)
{
	t_request	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}
int	heap_parent(int i)
{
	return ((i - 1) / 2);
}

int	heap_left(int i)
{
	return (2 * i + 1);
}

int	heap_right(int i)
{
	return (2 * i + 2);
}
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
