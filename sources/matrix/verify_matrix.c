/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_matrix.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ada-cruz <ada-cruz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 16:42:18 by ada-cruz          #+#    #+#             */
/*   Updated: 2024/02/07 16:42:19 by ada-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	matrix_length(double **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
		i++;
	return (i);
}

int	equal_matrices(double **a, int asize, double **b, int bsize)
{
	int	i;
	int	j;

	if (asize != bsize)
		return (0);
	i = -1;
	while (++i < asize)
	{
		j = -1;
		while (++j < asize)
			if (a[i][j] != b[i][j])
				return (0);
	}
	return (1);
}
