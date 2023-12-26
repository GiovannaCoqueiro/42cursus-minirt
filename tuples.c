# include <stdio.h>
# include <math.h>
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

int are_equals_tuple(t_coordinates a, t_coordinates b)
{
	if (are_equals(a.x, b.x) && are_equals(a.y, b.y) \
		&& are_equals(a.z, b.z) && are_equals(a.w, b.w))
		return (1);
	else
		return (0);
}

t_coordinates adding_tuples(t_coordinates a, t_coordinates b)
{
	t_coordinates new_tuple;

	new_tuple.x = a.x + b.x;
	new_tuple.y = a.y + b.y;
	new_tuple.z = a.z + b.z;
	new_tuple.w = a.w + b.w;
	return (new_tuple);
}

t_coordinates subtract_tuples(t_coordinates a, t_coordinates b)
{
	t_coordinates new_tuple;

	new_tuple.x = a.x - b.x;
	new_tuple.y = a.y - b.y;
	new_tuple.z = a.z - b.z;
	new_tuple.w = a.w - b.w;
	return (new_tuple);
}

t_coordinates negate_tuples(t_coordinates a)
{
	t_coordinates new_tuple;
	new_tuple.x = -1 * a.x;
	new_tuple.y = -1 * a.y;
	new_tuple.z = -1 * a.z;
	new_tuple.w = -1 * a.w;
	return (new_tuple);
}

t_coordinates multiply_tuples(double scalar, t_coordinates a)
{
    t_coordinates new_tuple;
    new_tuple.x = scalar * a.x;
    new_tuple.y = scalar * a.y;
    new_tuple.z = scalar * a.z;
    new_tuple.w = scalar * a.w;
    return (new_tuple);
}

t_coordinates divide_tuples(double scalar, t_coordinates a)
{
    t_coordinates new_tuple;
    new_tuple.x = a.x / scalar;
    new_tuple.y = a.y / scalar;
    new_tuple.z = a.z / scalar;
    new_tuple.w = a.w / scalar;
    return (new_tuple);
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
	y = -2.0;
	z = 3.0;
	w = -4.0;
	xx = 5.0;
	yy = 6.0;
	zz = 7.0;
	ww = 0.0;
	
	negate_tuples((t_coordinates){x, y, z, w});
	// if (!are_equals_tuple((t_coordinates){x, y, z, w}, (t_coordinates){xx, yy, zz, ww}))
	// 	printf("as tuplas não são iguais");
	// else
	// 	printf("elas são iguais");
	// if (!are_equals())
	// 	printf("os pontos não são iguais");
}
