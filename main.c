/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobroue <lobroue@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/24 19:50:29 by lobroue           #+#    #+#             */
/*   Updated: 2026/07/25 13:55:06 by lobroue          ###   ########.fr       */
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

// int main(void)
// {
//     t_heap  h;
//     int     i;

//     heap_init(&h, 10);
//     heap_push(&h, (t_request){1, 5});
//     heap_push(&h, (t_request){2, 3});
//     heap_push(&h, (t_request){3, 8});
//     heap_push(&h, (t_request){4, 1});

//     // ta boucle d'affichage existante
//     i = 0;
//     while (i < h.size)
//     {
//         printf("index %d: coder %d, key %ld\n", i, h.data[i].coder_id, h.data[i].key);
//         i++;
//     }

//     // AJOUTE ceci : la boucle de pop
//     while (h.size > 0)
//     {
//         t_request r = heap_pop(&h);
//         printf("pop: coder %d, key %ld\n", r.coder_id, r.key);
//     }

//     heap_free(&h);
//     return (0);
// }