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

double calculate_determinant(double **matrix)
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
			minor = calculate_determinant(submatrix);
			if (col % 2)
				determinant -= matrix[0][col] * minor;
			else
				determinant += matrix[0][col] * minor;
			free(submatrix);
		}
	}
	return (determinant);
}

double **cofactor_matrix(double **matrix)
{
	int col;
	int row;
	double **submatrix;
	double **cofactor;

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
			free(submatrix);
		}
	}
	return (cofactor);
}

double **invert_matrix(double **matrix)
{
	double **invert;
	double determinant;
	double **trans_matrix;
	int i;
	int j;

	invert = cofactor_matrix(matrix);
	determinant = calculate_determinant(matrix);
	i = -1;

	while (++i < matrix_length(matrix))
	{
		j = -1;
		while (++j < matrix_length(matrix))
			invert[i][j] = (invert[i][j]) / determinant;
	}
	trans_matrix = transposing_matrix(invert);
	free(invert);
	return (trans_matrix);
}

double **create_translation_matrix(t_coordinates tuple)
{
	double **translate_matrix;

	translate_matrix = creating_identity_matrix(4);
	translate_matrix[0][3] = tuple.x;
	translate_matrix[1][3] = tuple.y;
	translate_matrix[2][3] = tuple.z;
	return (translate_matrix);
}

double **create_scaling_matrix(t_coordinates tuple)
{
	double **scaling_matrix;

	scaling_matrix = creating_identity_matrix(4);
	scaling_matrix[0][0] = tuple.x;
	scaling_matrix[1][1] = tuple.y;
	scaling_matrix[2][2] = tuple.z;
	return (scaling_matrix);
}

// double **create_rotation_x_matrix(double axis)
// {
// 	double **rotation_x_matrix;
// 	double rad;

// 	rad = axis * (M_PI / 180)
// 	rotation_x_matrix = creating_identity_matrix(4);
// 	rotation_x_matrix[1][1] = cos(rad);
// 	rotation_x_matrix[1][2] = -sin(rad);
// 	rotation_x_matrix[2][1] = sin(rad);
// 	rotation_x_matrix[2][2] = cos(rad);
// 	return (rotation_x_matrix);
// }

double **shearing_matrix(double proportion[6])
{
	double **shearing_matrix;

	shearing_matrix = creating_identity_matrix(4);
	shearing_matrix[0][1] = proportion[0];
	shearing_matrix[0][2] = proportion[1];
	shearing_matrix[1][0] = proportion[2];
	shearing_matrix[1][2] = proportion[3];
	shearing_matrix[2][0] = proportion[4];
	shearing_matrix[2][1] = proportion[5];
	return (shearing_matrix);
}

int	main(void)
{
	double	**a;
	double	**b;
	double	**c;
	int		i;

	a = create_matrix(4);
	a[0][0] = 3;
	a[0][1] = -9;
	a[0][2] = 7;
	a[0][3] = 3;
	a[1][0] = 3;
	a[1][1] = -8;
	a[1][2] = 2;
	a[1][3] = -9;
	a[2][0] = -4;
	a[2][1] = 4;
	a[2][2] = 4;
	a[2][3] = 1;
	a[3][0] = -6;
	a[3][1] = 5;
	a[3][2] = -1;
	a[3][3] = 1;

	b = create_matrix(4);
	b[0][0] = 8;
	b[0][1] = 2;
	b[0][2] = 2;
	b[0][3] = 2;
	b[1][0] = 3;
	b[1][1] = -1;
	b[1][2] = 7;
	b[1][3] = 0;
	b[2][0] = 7;
	b[2][1] = 0;
	b[2][2] = 5;
	b[2][3] = 4;
	b[3][0] = 6;
	b[3][1] = -2;
	b[3][2] = 0;
	b[3][3] = 5;

	c = create_rotation_x_matrix()
	double **d = multiply_matrix(c, invert_matrix(b));
	i = -1;
	while (++i < 4)
	{
		int j = -1;
		while (++j < 4)
			printf("%f ", d[i][j]);
		printf("\n");
	}
}
