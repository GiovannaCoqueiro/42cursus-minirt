/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   determinant.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcoqueir <gcoqueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 16:42:05 by ada-cruz          #+#    #+#             */
/*   Updated: 2024/02/08 07:55:42 by gcoqueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	**calculate_submatrix(double **matrix, int row, int col)
{
	double	**submatrix;
	int		i;
	int		j;
	int		k;
	int		l;

	submatrix = create_matrix(matrix_length(matrix) - 1);
	i = -1;
	k = 0;
	while (++i < matrix_length(matrix))
	{
		if (i != row)
		{
			j = -1;
			l = 0;
			while (++j < matrix_length(matrix))
				if (j != col)
					submatrix[k][l++] = matrix[i][j];
			k++;
		}
	}
	return (submatrix);
}

double	**cofactor_matrix(double **matrix)
{
	int		col;
	int		row;
	double	**submatrix;
	double	**cofactor;

	cofactor = creating_identity_matrix(matrix_length(matrix));
	if (matrix_length(matrix) == 1)
		return (cofactor);
	row = -1;
	while (++row < matrix_length(matrix))
	{
		col = -1;
		while (++col < matrix_length(matrix))
		{
			submatrix = calculate_submatrix(matrix, row, col);
			cofactor[row][col] = calculate_determinant(submatrix);
			if ((row + col) % 2)
				cofactor[row][col] *= -1;
			free_matrix(submatrix);
		}
	}
	return (cofactor);
}

double	calculate_determinant(double **matrix)
{
	double	determinant;
	int		col;
	double	**submatrix;
	double	minor;

	determinant = 0;
	if (matrix_length(matrix) == 1)
		return (matrix[0][0]);
	else
	{
		col = -1;
		while (++col < matrix_length(matrix))
		{
			submatrix = calculate_submatrix(matrix, 0, col);
			minor = calculate_determinant(submatrix);
			if (col % 2)
				determinant -= matrix[0][col] * minor;
			else
				determinant += matrix[0][col] * minor;
			free_matrix(submatrix);
		}
	}
	return (determinant);
}
