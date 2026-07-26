/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobroue <lobroue@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/24 19:50:29 by lobroue           #+#    #+#             */
/*   Updated: 2026/07/26 19:50:43 by lobroue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	main(int argc, char **argv)
{
	t_table	table;

	if (parse_args(argc, argv, &table.params))
		return (1);
	if (init_table(&table))
		return (1);
	start_simulation(&table);
	cleanup(&table);
	return (0);
}

// int	main(int argc, char **argv)
// {
// 	t_table	table;

// 	if (parse_args(argc, argv, &table.params))
// 		return (1);
// 	if (init_table(&table))
// 		return (1);
// 	start_simulation(&table);
// 	free(table.coders);
// 	free(table.dongles);
// 	return (0);
// }
