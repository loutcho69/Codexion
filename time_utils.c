/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobroue <lobroue@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/24 19:50:36 by lobroue           #+#    #+#             */
/*   Updated: 2026/07/25 13:45:20 by lobroue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

long get_time_ms(void)
{
    struct timeval tv;

    gettimeofday(&tv, NULL);
    return ( (long)tv.tv_sec * 1000 + tv.tv_usec/1000 );
}

int simulation_stopped(t_table *table)
{
    int ret;

    pthread_mutex_lock(&table->stop_mutex);
    ret = table->stop;
    pthread_mutex_unlock(&table->stop_mutex);
    return (ret);
}
void log_state(t_table *table, int id, char *msg)
{
    pthread_mutex_lock(&table->print_mutex);
    if (!simulation_stopped(table))
        printf("%ld %d %s\n", get_time_ms() - table->start_time, id, msg);
    pthread_mutex_unlock(&table->print_mutex);
}
void precise_usleep(long duration_ms, t_table *table)
{
    long start;

    start = get_time_ms();
    while (get_time_ms() - start < duration_ms)
    {
        if (simulation_stopped(table))
            break;
        usleep(200);
    }
}
void	set_timeout(struct timespec *ts, long ms)
{
	clock_gettime(CLOCK_REALTIME, ts);
	ts->tv_nsec += ms * 1000000;
	while (ts->tv_nsec >= 1000000000)
	{
		ts->tv_sec += 1;
		ts->tv_nsec -= 1000000000;
	}
}