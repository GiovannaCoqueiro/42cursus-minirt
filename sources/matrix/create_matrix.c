/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_matrix.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcoqueir <gcoqueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 16:42:02 by ada-cruz          #+#    #+#             */
/*   Updated: 2024/02/08 15:29:56 by gcoqueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	**create_matrix(double size)
{
	double	**matrix;
	int		i;

	matrix = ft_calloc(size + 1, sizeof(double *));
	i = -1;
	while (++i < size)
	{
		matrix[i] = ft_calloc(size, sizeof(double));
	}
	return (matrix);
}

double	**transposing_matrix(double **matrix)
{
	int		size;
	int		i;
	int		j;
	double	**trans_matrix;

	size = matrix_length(matrix);
	trans_matrix = create_matrix(size);
	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			trans_matrix[j][i] = matrix[i][j];
			j++;
		}
		i++;
	}
	return (trans_matrix);
}

double	**invert_matrix(double **matrix)
{
	double	**invert;
	double	determinant;
	double	**trans_inverted_matrix;
	int		i;
	int		j;

	invert = cofactor_matrix(matrix);
	determinant = calculate_determinant(matrix);
	i = -1;
	while (++i < matrix_length(matrix))
	{
		j = -1;
		while (++j < matrix_length(matrix))
			invert[i][j] = (invert[i][j]) / determinant;
	}
	trans_inverted_matrix = transposing_matrix(invert);
	free_matrix(invert);
	return (trans_inverted_matrix);
}

double	**creating_identity_matrix(int size)
{
	int		i;
	double	**matrix;

	matrix = create_matrix(size);
	i = 0;
	while (i < size)
	{
		matrix[i][i] = 1;
		i++;
	}
	return (matrix);
}
