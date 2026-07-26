/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobroue <lobroue@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/24 19:50:33 by lobroue           #+#    #+#             */
/*   Updated: 2026/07/26 19:57:19 by lobroue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int parse_args(int argc, char **argv, t_params *params)
{
    if (argc != 9)
        return(error_print("not exacly 8 args"));
    if (parse_one_int(argv[1], &params->nb_coders))
        return(error_print("number_of_coders must be a positive integer"));
    if (parse_one_int(argv[2], &params->time_to_burnout))
        return(error_print("time_to_burnout must be a positive integer (in milliseconds)"));
    if (parse_one_int(argv[3], &params->time_to_compile))
        return(error_print("time_to_compile must be a positive integer (in milliseconds)"));
    if (parse_one_int(argv[4], &params->time_to_debug))
        return(error_print("time_to_debug must be a positive integer (in milliseconds)"));
    if (parse_one_int(argv[5], &params->time_to_refactor))
        return(error_print("time_to_refactor must be a positive integer (in milliseconds)"));
    if (parse_one_int(argv[6], &params->compiles_required))
        return(error_print("number_of_compiles_required must be a positive integer"));
    if (parse_one_int(argv[7], &params->dongle_cooldown))
        return(error_print("dongle_cooldown must be a non-negative integer (in milliseconds)"));
    if (parse_scheduler(argv[8], params))
        return(error_print("scheduler must be either 'fifo' or 'edf'"));
    return(0);
}