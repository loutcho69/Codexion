/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobroue <lobroue@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/24 19:50:07 by lobroue           #+#    #+#             */
/*   Updated: 2026/07/24 19:50:07 by lobroue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void take_dongle(t_dongle *dongle, t_coder *coder)
{
    pthread_mutex_lock(&dongle->mutex);
    while (dongle->taken
    || get_time_ms() < dongle->last_release
        + coder->table->params.dongle_cooldown)
        pthread_cond_wait(&dongle->available_cond, &dongle->mutex);
    dongle->taken = 1;
    pthread_mutex_unlock(&dongle->mutex);
    log_state(coder->table, coder->id, "has taken a dongle");
}
void *coder_routine(void *arg)
{
    t_coder *coder;

    coder = (t_coder *)arg;
    log_state(coder->table, coder->id, "is alive");
    return (NULL);
}

int start_simulation(t_table *table)
{
    int i;

    i = 0;
    while (i < table->params.nb_coders)
    {
        pthread_create(&table->coders[i].thread, NULL,
                       coder_routine, &table->coders[i]);
        i++;
    }
    i = 0;
    while (i < table->params.nb_coders)
    {
        pthread_join(table->coders[i].thread, NULL);
        i++;
    }
    return (0);
}