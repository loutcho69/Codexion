/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobroue <lobroue@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/26 19:46:15 by lobroue           #+#    #+#             */
/*   Updated: 2026/08/05 18:26:39 by lobroue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	heap_swap(t_request *a, t_request *b)
{
	t_request	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

int	heap_parent(int i)
{
	return ((i - 1) / 2);
}

int	heap_left(int i)
{
	return (2 * i + 1);
}

int	heap_right(int i)
{
	return (2 * i + 2);
}
