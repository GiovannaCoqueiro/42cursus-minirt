#include <X11/X.h>
#include <X11/keysym.h>
#include <math.h>
#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct s_coordinates
{
	double x;
	double y;
	double z;
	double w;
}	t_coordinates;

int	matrix_length(double **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
		i++;
	return (i);
}

double	**create_matrix(double size)
{
	double	**matrix;
	int		i;

	matrix = calloc(size + 1, sizeof(double *));
	i = -1;
	while (++i < size)
	{
		matrix[i] = calloc(size, sizeof(double));
	}
	return (matrix);
}

int	equal_matrixes(double **a, int asize, double **b, int bsize)
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
		{
			if (a[i][j] != b[i][j])
				return (0);
		}
	}
	return (1);
}

double	calculate_multiply_matrix(double **a, double **b, int row, int col)
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
			c[i][j] = calculate_multiply_matrix(a, b, i, j);
	}
	return (c);
}

double	calculate_multiply_matrix_tuple(double **a, double *tuple, int row)
{
	double	result;
	int		i;

	result = 0;
	i = -1;
	while (++i < 4)
	{
		result += (a[row][i] * tuple[i]);
	}
	return (result);
}

t_coordinates multiply_matrix_tuple(double **a, t_coordinates b)
{
	t_coordinates	tuple;

	tuple.x = a[0][0] * b.x + a[0][1] * b.y + a[0][2] * b.z + a[0][3] * b.w;
	tuple.y = a[1][0] * b.x + a[1][1] * b.y + a[1][2] * b.z + a[1][3] * b.w;
	tuple.z = a[2][0] * b.x + a[2][1] * b.y + a[2][2] * b.z + a[2][3] * b.w;
	tuple.w = a[3][0] * b.x + a[3][1] * b.y + a[3][2] * b.z + a[3][3] * b.w;
	return (tuple);
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

double	**transposing_matrix(double **matrix)
{
	int		size;
	int		i;
	int		j;
	double	**trans_matrix;

	size = matrix_length(matrix);
	trans_matrix = create_matrix(size);
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

// double determinant_2x2(double **matrix)
// {
// 	double determinant;

// 	determinant = matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
// 	return (determinant);
// }

double **calculate_submatrix(double **matrix, int row, int col)
{
	double **submatrix;
	int i;
	int j;
	int k;
	int l;

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
			{
				if (j != col)
				{
					submatrix[k][l] = matrix[i][j];
					l++;
				}
			}
			k++;
		}
	}
	return (submatrix);
}

// double	minor(double **matrix, int row, int col)
// {
// 	double **submatrix;
// 	double determinant;

// 	submatrix = calculate_submatrix(matrix, row, col);
// 	determinant = determinant_2x2(submatrix);
// 	free(submatrix);
// 	return (determinant);
// }

// double cofactor(double **matrix, int row, int col)
// {
// 	double determinant;

// 	determinant = minor(matrix, row, col);
// 	if ((row + col) % 2  != 0)
// 		determinant *= -1;
// 	return (determinant);
// }
// double determinant_3x3(double **matrix)
// {
// 	double determinant;
// 	int col;

// 	determinant = 0;

// 	col = -1;
// 	while (++col < matrix_length(matrix))
// 		determinant += matrix[0][col] * cofactor(matrix, 0, col);
// 	return (determinant);
// }

double determinant_4x4(double **matrix)
{
	double determinant;
	int col;
	double **submatrix;
	double minor;

	determinant = 0;
	if (matrix_length(matrix) == 1)
		return (matrix[0][0]);
	else
	{
		col = -1;
		while (++col < matrix_length(matrix))
		{
			submatrix = calculate_submatrix(matrix, 0, col);
			minor = determinant_4x4(submatrix);
			if (col % 2)
				determinant -= matrix[0][col] * minor;
			else
				determinant += matrix[0][col] * minor;
			free(submatrix);
		}
	}
	return (determinant);
}

int	main(void)
{
	double	**a;
	double	**b;
	double	d[4];
	double	*c;
	int		i;

	a = create_matrix(4);
	// b = create_matrix(4);
	a[0][0] = -2;
	a[0][1] = -8;
	a[0][2] = 3;
	a[0][3] = 5;
	a[1][0] = -3;
	a[1][1] = 1;
	a[1][2] = 7;
	a[1][3] = 3;
	a[2][0] = 1;
	a[2][1] = 2;
	a[2][2] = -9;
	a[2][3] = 6;
	a[3][0] = -6;
	a[3][1] = 7;
	a[3][2] = 7;
	a[3][3] = -9;
	printf("%f\n", determinant_4x4(a));
	// printf("%f\n", determinant_2x2(a));
}
