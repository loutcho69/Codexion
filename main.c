/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobroue <lobroue@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/24 19:50:29 by lobroue           #+#    #+#             */
/*   Updated: 2026/07/25 11:29:18 by lobroue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

#include "codexion.h"

int main(void)
{
    t_heap h;
    int    i;

    heap_init(&h, 10);
    heap_push(&h, (t_request){1, 5});
    heap_push(&h, (t_request){2, 3});
    heap_push(&h, (t_request){3, 8});
    heap_push(&h, (t_request){4, 1});
    i = 0;
    while (i < h.size)
    {
        printf("index %d: coder %d, key %ld\n", i, h.data[i].coder_id, h.data[i].key);
        i++;
    }
    heap_free(&h);
    return (0);
}