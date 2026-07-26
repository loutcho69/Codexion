/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobroue <lobroue@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/26 19:44:52 by lobroue           #+#    #+#             */
/*   Updated: 2026/07/26 21:48:46 by lobroue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void set_last_compil(t_coder *coder, long time)
{
    pthread_mutex_lock(&coder->state_mutex);
    coder->last_compil_start = time;
    pthread_mutex_unlock(&coder->state_mutex);
}
