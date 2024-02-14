/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcoqueir <gcoqueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 15:49:20 by gcoqueir          #+#    #+#             */
/*   Updated: 2024/02/08 15:49:35 by gcoqueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	free_intersections(t_intersections **intersec)
{
	t_intersections	*temp;

	while (*intersec)
	{
		temp = (*intersec)->next;
		free(*intersec);
		*intersec = NULL;
		(*intersec) = temp;
	}
}
