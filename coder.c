/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobroue <lobroue@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/24 19:50:07 by lobroue           #+#    #+#             */
/*   Updated: 2026/08/04 00:53:49 by lobroue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	take_dongle(t_dongle *dongle, t_coder *coder)
{
	t_request		req;
	struct timespec	ts;

	req.coder_id = coder->id;
	req.key = compute_key(coder);
	pthread_mutex_lock(&dongle->mutex);
	heap_push(&dongle->queue, req);
	while (dongle->taken
		|| get_time_ms() < dongle->last_release
			+ coder->table->params.dongle_cooldown
		|| heap_peek(&dongle->queue).coder_id != coder->id)
	{
		if (simulation_stopped(coder->table))
		{
			heap_pop(&dongle->queue);
			pthread_mutex_unlock(&dongle->mutex);
			return ;
		}
		set_timeout(&ts, 1);
		pthread_cond_timedwait(&dongle->available_cond, &dongle->mutex, &ts);
	}
	heap_pop(&dongle->queue);
	dongle->taken = 1;
	pthread_mutex_unlock(&dongle->mutex);
	log_state(coder->table, coder->id, "has taken a dongle");
}
void release_dongle(t_dongle *dongle)
{
    pthread_mutex_lock(&dongle->mutex);
    dongle->taken = 0;
    dongle->last_release = get_time_ms();
    pthread_cond_broadcast(&dongle->available_cond);
    pthread_mutex_unlock(&dongle->mutex);
}

void	take_both_dongles(t_coder *coder)
{
	t_dongle	*left;
	t_dongle	*right;

	left = &coder->table->dongles[coder->left_dongle];
	right = &coder->table->dongles[coder->right_dongle];
	if (coder->id % 2 == 0)
	{
		take_dongle(left, coder);
		take_dongle(right, coder);
	}
	else
	{
		take_dongle(right, coder);
		take_dongle(left, coder);
	}
}
void	*coder_routine(void *arg)
{
	t_coder	*coder;

	coder = (t_coder *)arg;
	while (!simulation_stopped(coder->table))
	{
		take_both_dongles(coder);
		set_last_compil(coder, get_time_ms());
		log_state(coder->table, coder->id, "is compiling");
		increment_compil(coder);
		precise_usleep(coder->table->params.time_to_compile, coder->table);
		release_dongle(&coder->table->dongles[coder->left_dongle]);
		release_dongle(&coder->table->dongles[coder->right_dongle]);
		log_state(coder->table, coder->id, "is debugging");
		precise_usleep(coder->table->params.time_to_debug, coder->table);
		log_state(coder->table, coder->id, "is refactoring");
		precise_usleep(coder->table->params.time_to_refactor, coder->table);
	}
	return (NULL);
}
int	start_simulation(t_table *table)
{
	pthread_t	monitor;
	int			i;

	i = 0;
	while (i < table->params.nb_coders)
	{
		pthread_create(&table->coders[i].thread, NULL,
			coder_routine, &table->coders[i]);
		i++;
	}
	pthread_create(&monitor, NULL, monitor_routine, table);
	pthread_join(monitor, NULL);
	i = 0;
	while (i < table->params.nb_coders)
	{
		pthread_join(table->coders[i].thread, NULL);
		i++;
	}
	return (0);
}