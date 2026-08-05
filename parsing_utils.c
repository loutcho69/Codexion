/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobroue <lobroue@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/26 19:56:53 by lobroue           #+#    #+#             */
/*   Updated: 2026/08/05 18:34:23 by lobroue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	is_valid_number(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '\0')
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	ft_atoi_safe(char *str, int *result)
{
	int	i;
	int	digit;

	i = 0;
	*result = 0;
	while (str[i])
	{
		digit = str[i] - '0';
		if (*result > (INT_MAX - digit) / 10)
			return (1);
		*result = *result * 10 + digit;
		i++;
	}
	return (0);
}

int	parse_one_int(char *str, int *dest)
{
	if (!is_valid_number(str))
		return (1);
	if (ft_atoi_safe(str, dest))
		return (1);
	return (0);
}

int	parse_scheduler(char *argv, t_params *params)
{
	if (strcmp(argv, "fifo") == 0)
		params->scheduler = 1;
	else if (strcmp(argv, "edf") == 0)
		params->scheduler = 0;
	else
		return (1);
	return (0);
}

int	error_print(char *str)
{
	fprintf(stderr, "Error: %s.\n", str);
	return (1);
}
