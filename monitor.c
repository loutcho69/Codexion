/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobroue <lobroue@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/24 23:09:25 by lobroue           #+#    #+#             */
/*   Updated: 2026/07/26 19:55:53 by lobroue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	check_burnout(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->params.nb_coders)
	{
		if (get_time_ms() - get_last_compil(&table->coders[i])
			> table->params.time_to_burnout)
		{
			log_state(table, table->coders[i].id, "burned out");
			set_stop(table);
			return (1);
		}
		i++;
	}
	return (0);
}
void	*monitor_routine(void *arg)
{
	t_table	*table;

	table = (t_table *)arg;
	while (1)
	{
		if (check_burnout(table))
			return (NULL);
		if (all_compiled_enough(table))
		{
			set_stop(table);
			return (NULL);
		}
		usleep(1000);
	}
	return (NULL);
}
