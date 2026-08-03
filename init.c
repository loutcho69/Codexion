/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobroue <lobroue@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/24 19:50:27 by lobroue           #+#    #+#             */
/*   Updated: 2026/08/04 00:59:32 by lobroue          ###   ########.fr       */
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
int	init_dongles(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->params.nb_coders)
	{
		table->dongles[i].id = i;
		table->dongles[i].taken = 0;
		table->dongles[i].last_release = 0;
		pthread_mutex_init(&table->dongles[i].mutex, NULL);
		pthread_cond_init(&table->dongles[i].available_cond, NULL);
		if (heap_init(&table->dongles[i].queue, table->params.nb_coders))
			return (1);
		i++;
	}
	return (0);
}

void init_coders(t_table *table)
{
    int i;

    i = 0;
    while (i < table->params.nb_coders)
    {
        table->coders[i].id = i + 1;
        table->coders[i].compil_count = 0;
        table->coders[i].last_compil_start = table->start_time;
        table->coders[i].table = table;
        table->coders[i].left_dongle = i;
        table->coders[i].right_dongle = (i + 1) % table->params.nb_coders;
        pthread_mutex_init(&table->coders[i].state_mutex, NULL);
        i++;
    }
}

int	init_dongles(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->params.nb_coders)
	{
		table->dongles[i].id = i;
		table->dongles[i].taken = 0;
		table->dongles[i].last_release = 0;
		pthread_mutex_init(&table->dongles[i].mutex, NULL);
		pthread_cond_init(&table->dongles[i].available_cond, NULL);
		if (heap_init(&table->dongles[i].queue, table->params.nb_coders))
		{
			pthread_mutex_destroy(&table->dongles[i].mutex);
			pthread_cond_destroy(&table->dongles[i].available_cond);
			destroy_dongles(table, i);
			return (1);
		}
		i++;
	}
	return (0);
}
