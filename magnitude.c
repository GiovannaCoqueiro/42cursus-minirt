# include <stdio.h>
# include <math.h>
#include <stdlib.h>
# define EPSILON 0.0001

typedef struct s_coordinates
{
	double x;
	double y;
	double z;
	double w;
}	t_coordinates;

int	are_equals(double a, double b)
{
	if (fabs(a - b) < EPSILON)
		return (1);
	return (0);
}

double	calculate_vector_magnitude(t_coordinates v)
{
	return (sqrt(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2) + pow(v.w, 2)));
}

int	validate_normalized_vector(t_coordinates coordinates)
{
	return (are_equals(calculate_vector_magnitude(coordinates), 1));
}

void    normalize_vector(t_coordinates *coordinates)
{
    coordinates->x = coordinates->x/calculate_vector_magnitude(*coordinates);
    coordinates->y = coordinates->y/calculate_vector_magnitude(*coordinates);
    coordinates->z = coordinates->z/calculate_vector_magnitude(*coordinates);
    coordinates->w = coordinates->w/calculate_vector_magnitude(*coordinates);
}

double dot_product(t_coordinates a, t_coordinates b)
{
    double new_coor;

    new_coor = a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
    return (new_coor);
}

t_coordinates cross_product(t_coordinates a, t_coordinates b)
{
    t_coordinates new_coor;

    new_coor.x = a.y * b.z - a.z * b.y;
    new_coor.y = a.z * b.x - a.x * b.z;
    new_coor.z = a.x * b.y - a.y * b.x;
    new_coor.w = 0.0;
    return (new_coor);
}

int main(void)
{
	double x;
	double y;
	double z;
	double w;
	double ww;
	double xx;
	double yy;
	double zz;
	
	
	x = 1.0;
	y = 2.0;
	z = 3.0;
	w = 0.0;
	xx = 2.0;
	yy = 3.0;
	zz = 4.0;
	ww = 0.0;
	
    t_coordinates coor;

    coor.x = 0.0;
    coor.y = 0.0;
    coor.z = 1.0;
    coor.w = 0.0;
    // double magnitude = calculate_vector_magnitude(coor);
    // printf("magnitude: %f\n", magnitude);
    // int teste = validate_normalized_vector(coor);
    // printf("normalizado: %d\n", teste);
    // printf("x: %f   y: %f   z: %f\n", coor.x, coor.y, coor.z);
    
    // normalize_vector(&coor);
    // printf("\npós normalização:\n");
    // magnitude = calculate_vector_magnitude(coor);
    // printf("magnitude: %f\n", magnitude);
    // teste = validate_normalized_vector(coor);
    // printf("normalizado: %d\n", teste);
    // printf("x: %f   y: %f   z: %f\n", coor.x, coor.y, coor.z);


    t_coordinates teste1 = cross_product((t_coordinates){x, y, z, w}, (t_coordinates){xx, yy, zz, ww});
    printf("x: %f   y: %f   z: %f\n", teste1.x, teste1.y, teste1.z);

    t_coordinates teste2 = cross_product((t_coordinates){xx, yy, zz, ww}, (t_coordinates){x, y, z, w});
    printf("x: %f   y: %f   z: %f\n", teste2.x, teste2.y, teste2.z);


    // printf("%f\n", sqrt(14));
	// negate_tuples((t_coordinates){x, y, z, w});
	// if (!are_equals_tuple((t_coordinates){x, y, z, w}, (t_coordinates){xx, yy, zz, ww}))
	// 	printf("as tuplas não são iguais");
	// else
	// 	printf("elas são iguais");
	// if (!are_equals())
	// 	printf("os pontos não são iguais");
}
