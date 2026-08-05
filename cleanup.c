/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobroue <lobroue@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/25 13:54:05 by lobroue           #+#    #+#             */
/*   Updated: 2026/08/04 01:03:08 by lobroue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	cleanup(t_table *table)
{
	int	i;

	destroy_dongles(table, table->params.nb_coders);
	i = 0;
	while (i < table->params.nb_coders)
	{
		pthread_mutex_destroy(&table->coders[i].state_mutex);
		i++;
	}
	pthread_mutex_destroy(&table->print_mutex);
	pthread_mutex_destroy(&table->stop_mutex);
	pthread_mutex_destroy(&table->seq_mutex);
	free(table->coders);
	free(table->dongles);
}

void	heap_free(t_heap *heap)
{
	free(heap->data);
}

void	destroy_dongles(t_table *table, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		pthread_mutex_destroy(&table->dongles[i].mutex);
		pthread_cond_destroy(&table->dongles[i].available_cond);
		heap_free(&table->dongles[i].queue);
		i++;
	}
}
