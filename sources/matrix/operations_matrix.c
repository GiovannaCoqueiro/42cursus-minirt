/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_matrix.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ada-cruz <ada-cruz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 16:42:08 by ada-cruz          #+#    #+#             */
/*   Updated: 2024/02/07 16:42:09 by ada-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static double	calculate_result(double **a, double **b, int row, int col)
{
	double	result;
	int		i;

	result = 0;
	i = -1;
	while (++i < 4)
	{
		result += (a[row][i] * b[i][col]);
	}
	return (result);
}

double	**multiply_matrix(double **a, double **b)
{
	int		i;
	int		j;
	double	**c;

	c = create_matrix(4);
	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
			c[i][j] = calculate_result(a, b, i, j);
	}
	return (c);
}

t_coordinates	multiply_matrix_tuple(double **a, t_coordinates b)
{
	t_coordinates	tuple;

	tuple.x = a[0][0] * b.x + a[0][1] * b.y + a[0][2] * b.z + a[0][3] * b.w;
	tuple.y = a[1][0] * b.x + a[1][1] * b.y + a[1][2] * b.z + a[1][3] * b.w;
	tuple.z = a[2][0] * b.x + a[2][1] * b.y + a[2][2] * b.z + a[2][3] * b.w;
	tuple.w = a[3][0] * b.x + a[3][1] * b.y + a[3][2] * b.z + a[3][3] * b.w;
	return (tuple);
}

double	**multiply_matrix_scalar(double scalar, double **matrix)
{
	int		i;
	int		j;
	double	**scalar_matrix;

	scalar_matrix = create_matrix(matrix_length(matrix));
	i = 0;
	while (i < matrix_length(matrix))
	{
		j = 0;
		while (j < matrix_length(matrix))
		{
			scalar_matrix[i][j] = scalar * matrix[i][j];
			j++;
		}
		i++;
	}
	return (scalar_matrix);
}
