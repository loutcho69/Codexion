/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobroue <lobroue@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/24 19:50:33 by lobroue           #+#    #+#             */
/*   Updated: 2026/08/05 18:34:02 by lobroue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	parse_args(int argc, char **argv, t_params *params)
{
	if (argc != 9)
		return (error_print("expected 8 arguments"));
	if (parse_one_int(argv[1], &params->nb_coders))
		return (error_print("invalid number_of_coders"));
	if (parse_one_int(argv[2], &params->time_to_burnout))
		return (error_print("invalid time_to_burnout"));
	if (parse_one_int(argv[3], &params->time_to_compile))
		return (error_print("invalid time_to_compile"));
	if (parse_one_int(argv[4], &params->time_to_debug))
		return (error_print("invalid time_to_debug"));
	if (parse_one_int(argv[5], &params->time_to_refactor))
		return (error_print("invalid time_to_refactor"));
	if (parse_one_int(argv[6], &params->compiles_required))
		return (error_print("invalid number_of_compiles_required"));
	if (parse_one_int(argv[7], &params->dongle_cooldown))
		return (error_print("invalid dongle_cooldown"));
	if (parse_scheduler(argv[8], params))
		return (error_print("scheduler must be 'fifo' or 'edf'"));
	if (params->nb_coders < 1)
		return (error_print("number_of_coders must be at least 1"));
	return (0);
}
