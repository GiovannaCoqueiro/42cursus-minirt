#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <X11/keysym.h>
#include <X11/X.h>
#include <mlx.h>

double **create_matrix(double size)
{
    double **matrix;
    int     i;

    matrix = calloc(size + 1, sizeof(double *));
    i = -1;
    while (++i < size)
    {
        matrix[i] = calloc(size, sizeof(double));
    }
    return (matrix);
}

int equal_matrixes(double **a, int asize, double **b, int bsize)
{
    int i;
    int j;

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

double calculate_multiply_matrix(double **a, double **b, int row, int col)
{
    double result;
    int i;

    result = 0;
    i = -1;
    while (++i < 4)
    {
        result += (a[row][i] * b[i][col]);
    }
    return (result);
}

double **multiply_matrix(double **a, double **b)
{
    int i;
    int j;
    double **c;

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

double calculate_multiply_matrix_tuple(double **a, double *tuple, int row)
{
    double result;
    int i;

    result = 0;
    i = -1;
    while (++i < 4)
    {
        result += (a[row][i] * tuple[i]);
    }
    return (result);
}

double *multiply_matrix_tuple(double **a, double *tuple)
{
    int i;
    int j;
    double *c;

    c = calloc(sizeof(double), 4);
    i = -1;
    while (++i < 4)
    {
        c[i] = calculate_multiply_matrix_tuple(a, tuple, i);
    }
    return (c);
}

int main(void)
{
    double **a = create_matrix(4);
    double **b = create_matrix(4);
    a[0][0] = 1;
    a[0][1] = 2;
    a[0][2] = 3;
    a[0][3] = 4;
    a[1][0] = 2;
    a[1][1] = 4;
    a[1][2] = 4;
    a[1][3] = 2;
    a[2][0] = 8;
    a[2][1] = 6;
    a[2][2] = 4;
    a[2][3] = 1;
    a[3][0] = 0;
    a[3][1] = 0;
    a[3][2] = 0;
    a[3][3] = 1;
 
    b[0][0] = -2;
    b[0][1] = 1;
    b[0][2] = 2;
    b[0][3] = 3;
    b[1][0] = 3;
    b[1][1] = 2;
    b[1][2] = 1;
    b[1][3] = -1;
    b[2][0] = 4;
    b[2][1] = 3;
    b[2][2] = 6;
    b[2][3] = 5;
    b[3][0] = 1;
    b[3][1] = 2;
    b[3][2] = 7;
    b[3][3] = 8;
    double d[4] = {1, 2, 3, 1};
    double *c = multiply_matrix_tuple(a, d);
    int i = -1;
    while (++i < 4)
    {
        printf("%f ", c[i]);
        if (i == 3)
            printf("\n");
    }
    printf("%d\n", equal_matrixes(a, 4, b, 4));
}
