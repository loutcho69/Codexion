/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobroue <lobroue@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/24 19:50:27 by lobroue           #+#    #+#             */
/*   Updated: 2026/07/26 19:48:27 by lobroue          ###   ########.fr       */
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
void	init_dongles(t_table *table)
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
		heap_init(&table->dongles[i].queue, table->params.nb_coders);
		i++;
	}
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

int init_table(t_table *table) 
{
    table->coders = malloc(sizeof(t_coder) * table->params.nb_coders);
    if (!table->coders)
        return (1);
    table->dongles = malloc(sizeof(t_dongle) * table->params.nb_coders);
    if (!table->dongles)
    {
        free(table->coders);
        return (1);
    }
    table->stop = 0;
    table->start_time = get_time_ms();
    pthread_mutex_init(&table->print_mutex, NULL);
    pthread_mutex_init(&table->stop_mutex, NULL);
    table->seq_counter = 0;
    pthread_mutex_init(&table->seq_mutex, NULL);    
    init_dongles(table);
    init_coders(table);
    return (0);
}