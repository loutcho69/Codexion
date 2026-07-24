/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobroue <lobroue@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/24 23:09:25 by lobroue           #+#    #+#             */
/*   Updated: 2026/07/24 23:11:13 by lobroue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

long	get_last_compil(t_coder *coder)
{
	long	ret;

	pthread_mutex_lock(&coder->state_mutex);
	ret = coder->last_compil_start;
	pthread_mutex_unlock(&coder->state_mutex);
	return (ret);
}

void	set_stop(t_table *table)
{
	pthread_mutex_lock(&table->stop_mutex);
	table->stop = 1;
	pthread_mutex_unlock(&table->stop_mutex);
}

void	*monitor_routine(void *arg)
{
	t_table	*table;
	int		i;

	table = (t_table *)arg;
	while (1)
	{
		i = 0;
		while (i < table->params.nb_coders)
		{
			if (get_time_ms() - get_last_compil(&table->coders[i])
				> table->params.time_to_burnout)
			{
				log_state(table, table->coders[i].id, "burned out");
				set_stop(table);
				return (NULL);
			}
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}