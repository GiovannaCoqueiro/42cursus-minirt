/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcoqueir <gcoqueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 16:34:36 by ada-cruz          #+#    #+#             */
/*   Updated: 2024/02/09 14:37:26 by gcoqueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>
# include "libft.h"
# include <mlx.h>
# include <X11/keysym.h>
# include <X11/X.h>
# include <fcntl.h>
# include <math.h>

# define VECTOR 0
# define POINT 1
# define EPSILON 0.0001
# define XROT 1
# define YROT 2
# define ZROT 3
# define HALF_QUARTER 45
# define FULL_QUARTER 90
# define SP 1
# define PL 2
# define CY 3
# define WIDTH 800
# define HEIGHT 800

typedef struct s_coordinates
{
	double	x;
	double	y;
	double	z;
	double	w;
}	t_coordinates;

typedef struct s_ray
{
	t_coordinates	origin;
	t_coordinates	direction;
}	t_ray;

typedef struct s_delta
{
	t_coordinates	object_to_ray;
	double			a;
	double			b;
	double			c;
	double			delta;
	double			t[2];
}	t_delta;

typedef struct s_color
{
	int	red;
	int	green;
	int	blue;	
}	t_color;

typedef struct s_amb_light
{
	int		amb_light;
	double	ratio;
	t_color	color;
}	t_amb_light;

typedef struct s_light
{
	int				light;
	t_coordinates	point;
	double			brightness;
	t_color			color;
}	t_light;

typedef struct s_camera
{
	int				camera;
	t_coordinates	point;
	t_coordinates	vector;
	double			fov;
	double			**trans_matrix;
	double			**invert_matrix;
}	t_camera;

typedef struct s_material
{
	double	ambient;
	double	diffuse;
	double	specular;
	double	shininess;
}	t_material;

typedef struct s_sphere
{
	t_coordinates	point;
	double			diameter;
	t_color			color;
	double			**inverse_matrix;
	double			**transpose_matrix;
}	t_sphere;

typedef struct s_plane
{
	t_coordinates	point;
	t_coordinates	vector;
	t_color			color;
	t_color			color1;
	double			**inverse_matrix;
	double			**transpose_matrix;
}	t_plane;

typedef struct s_cylinder
{
	t_coordinates	point;
	t_coordinates	vector;
	double			diameter;
	double			height;
	double			min;
	double			max;
	t_color			color;
	t_color			color1;
	double			**inverse_matrix;
	double			**transpose_matrix;
}	t_cylinder;

typedef struct s_hit
{
	int				object;
	int				count;
	double			t[100];
	t_coordinates	hit_point[100];
	t_ray			ray;
	t_color			color;
	t_sphere		*sphere;
	t_plane			*plane;
	t_cylinder		*cylinder;
}	t_hit;

typedef struct s_intersections
{
	int						object;
	double					t;
	t_ray					ray;
	t_coordinates			hit_point;
	t_coordinates			eye;
	t_coordinates			normal;
	t_coordinates			over_point;
	t_color					color;
	int						inside;
	t_sphere				*sphere;
	t_plane					*plane;
	t_cylinder				*cylinder;
	struct s_intersections	*next;
}	t_intersections;

typedef struct s_mlx
{
	void	*mlx;
	void	*window;
	void	*image;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_mlx;

typedef struct s_rt
{
	char			**linesread;
	char			**lineread;
	char			**color;
	char			**coordinates;
	t_amb_light		amb_light;
	t_camera		camera;
	t_light			light;
	t_material		*material;
	t_sphere		*sphere;
	t_plane			*planes;
	t_cylinder		*cylinders;
	t_intersections	*intersects;
	int				num_sp;
	int				num_pl;
	int				num_cy;
	double			pixel_size;
	double			half_width;
	double			half_height;
	t_mlx			mlx;
}	t_rt;

double			degree_to_rad(double degree);
void			minirt(t_rt *rt);

/* color */
t_color			adding_colors(t_color a, t_color b);
t_color			subtract_colors(t_color a, t_color b);
t_color			multiply_color_by_scalar(t_color material, double scalar);
t_color			multiply_colors(t_color a, t_color b);

/* finish */
void			print_error(char *error, t_rt *rt);
void			free_ptrptr(char ***ptrptr);
void			free_matrix(double **matrix);
void			free_rt(t_rt *rt);
void			free_intersections(t_intersections **intersec);

/* init */
t_rt			*init_rt(void);
void			set_material(t_material *material);
void			set_transformations(t_rt *rt);
void			set_mlx(t_rt *rt);
void			set_pixel_size(t_rt *rt);

/* intersections */
void			view_transformation(t_rt *rt, t_coordinates up);
void			aux_view_transformation(t_rt *rt);
t_ray			ray_for_pixel(t_rt *rt, double x, double y);
t_delta			delta_intersect_ray_sphere(t_ray ray);
void			intersect_sphere(t_rt *rt, t_ray ray, \
					t_intersections **intersec);
void			spheres_transformations(t_rt *rt);
t_hit			ray_sphere_intersections(t_ray ray, t_sphere *sphere);
void			intersect_plane(t_rt *rt, t_ray ray, \
					t_intersections **intersec);
t_hit			ray_plane_intersections(t_ray ray, t_plane *plane);
void			planes_transformations(t_rt *rt);
t_delta			delta_intersect_ray_cylinder(t_ray ray);
void			intersect_cylinder(t_rt *rt, t_ray ray, \
					t_intersections **intersec);
void			cylinders_transformations(t_rt *rt);
t_hit			ray_cylinder_intersections(t_ray ray, t_cylinder *cylinder);
void			intersect_cylinder_cap(t_ray ray, t_ray old_ray, \
					t_cylinder *cylinder, t_hit *hit);
t_intersections	*new_intersec(t_ray ray, int i, t_hit new);
void			list_intersec_position(t_intersections **intersec, \
					t_intersections *new);
void			add_intersection(t_intersections **intersec, t_hit new, \
					t_ray ray);
void			get_intersections(t_rt *rt, t_intersections **intersections, \
					t_ray ray);
t_intersections	*hit_point(t_intersections **intersec);
t_ray			create_ray(t_coordinates point, t_coordinates vector);
t_coordinates	find_position(t_ray ray, double t);
t_ray			ray_transformation(t_ray ray, double **matrix);
t_coordinates	normal_vector_sphere(t_sphere *sphere, t_coordinates w_point);
t_coordinates	normal_vector_cylinder(t_cylinder *cy, t_coordinates w_point);
void			normal_object(t_intersections *temp);
t_coordinates	eye_vector(t_coordinates vector);
t_coordinates	reflect_vector(t_coordinates in, t_coordinates normal);
t_coordinates	light_vector(t_coordinates vector, t_coordinates point);

/* matrix */
double			**create_matrix(double size);
double			**invert_matrix(double **matrix);
double			**creating_identity_matrix(int size);
double			**transposing_matrix(double **matrix);
double			**calculate_submatrix(double **matrix, int row, int col);
double			**cofactor_matrix(double **matrix);
double			calculate_determinant(double **matrix);
double			**multiply_matrix(double **a, double **b);
t_coordinates	multiply_matrix_tuple(double **a, t_coordinates b);
double			**multiply_matrix_scalar(double scalar, double **matrix);
double			**create_rotation_x_matrix(double degree);
double			**create_rotation_y_matrix(double degree);
double			**create_rotation_z_matrix(double degree);
double			**calculate_z_y_rotation_matrix(t_coordinates vector);
double			**calculate_z_x_rotation_matrix(t_coordinates vector);
double			**calculate_rotation(t_coordinates vector);
double			**create_translation_matrix(t_coordinates tuple);
double			**create_scaling_matrix(t_coordinates tuple);
double			**create_shearing_matrix(double proportion[6]);
int				matrix_length(double **matrix);
int				equal_matrices(double **a, int asize, double **b, int bsize);

/* parser */
void			add_objects(t_rt *rt);
void			parser(t_rt *rt);
void			set_coordinates(t_coordinates *dest, char **src, double w);
void			set_color(t_color *dest, char **src);
void			validate_elements(t_rt *rt);
int				validate_normalized_vector(t_coordinates coordinates);
int				validate_angle(char *angle);
int				validate_color(char **color);
int				validate_coordinates(char **coordinates);
int				validate_double(char *number);
int				validate_int(char *number);
void			validate_sphere(t_rt *rt, int sp);
void			validate_plane(t_rt *rt, int pl);
void			validate_cylinder(t_rt *rt, int cy);

/* render */
t_color			intensity(t_rt *rt, t_intersections *hit, int is_shadowed);
t_color			result_color(t_rt *rt, t_ray ray);
int				is_shadowed(t_rt *rt, t_coordinates point);
void			render(t_rt *rt);

/* tuples */
int				are_equals(double a, double b);
int				are_equals_tuple(t_coordinates a, t_coordinates b);
t_coordinates	create_point(double x, double y, double z);
t_coordinates	create_vector(double x, double y, double z);
t_coordinates	adding_tuples(t_coordinates a, t_coordinates b);
t_coordinates	subtract_tuples(t_coordinates a, t_coordinates b);
t_coordinates	multiply_tuples(double scalar, t_coordinates a);
t_coordinates	divide_tuples(double scalar, t_coordinates a);
t_coordinates	negate_tuples(t_coordinates a);
double			calculate_vector_magnitude(t_coordinates v);
void			normalize_vector(t_coordinates *coordinates);
double			dot_product(t_coordinates a, t_coordinates b);
t_coordinates	cross_product(t_coordinates a, t_coordinates b);

#endif