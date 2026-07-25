/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobroue <lobroue@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/25 13:54:05 by lobroue           #+#    #+#             */
/*   Updated: 2026/07/25 13:54:15 by lobroue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	cleanup(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->params.nb_coders)
	{
		pthread_mutex_destroy(&table->dongles[i].mutex);
		pthread_cond_destroy(&table->dongles[i].available_cond);
		heap_free(&table->dongles[i].queue);
		pthread_mutex_destroy(&table->coders[i].state_mutex);
		i++;
	}
	pthread_mutex_destroy(&table->print_mutex);
	pthread_mutex_destroy(&table->stop_mutex);
	pthread_mutex_destroy(&table->seq_mutex);
	free(table->coders);
	free(table->dongles);
}