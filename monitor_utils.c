/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobroue <lobroue@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/26 19:54:27 by lobroue           #+#    #+#             */
/*   Updated: 2026/07/26 19:54:39 by lobroue          ###   ########.fr       */
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

void	increment_compil(t_coder *coder)
{
	pthread_mutex_lock(&coder->state_mutex);
	coder->compil_count++;
	pthread_mutex_unlock(&coder->state_mutex);
}

int	get_compil_count(t_coder *coder)
{
	int	ret;

	pthread_mutex_lock(&coder->state_mutex);
	ret = coder->compil_count;
	pthread_mutex_unlock(&coder->state_mutex);
	return (ret);
}

int	all_compiled_enough(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->params.nb_coders)
	{
		if (get_compil_count(&table->coders[i])
			< table->params.compiles_required)
			return (0);
		i++;
	}
	return (1);
}
