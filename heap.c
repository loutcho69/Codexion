/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobroue <lobroue@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/25 11:22:36 by lobroue           #+#    #+#             */
/*   Updated: 2026/07/25 11:28:54 by lobroue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int heap_init(t_heap *heap, int capacity)
{
    heap->data = malloc(sizeof(t_request) * capacity);
    if (!heap->data)
        return (1);
    heap->size = 0;
    heap->capacity = capacity;
    return (0);
}

void heap_free(t_heap *heap)
{
    free(heap->data);
}

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