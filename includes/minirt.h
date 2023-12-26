/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcoqueir <gcoqueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 16:34:36 by ada-cruz          #+#    #+#             */
/*   Updated: 2023/12/26 10:18:24 by gcoqueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "../libft/includes/libft.h"
# include "MLX42.h"
# include <fcntl.h>
# include <math.h>

# define WIDTH 400
# define HEIGHT 400
# define VECTOR 0
# define POINT 1
# define EPSILON 0.0001

typedef struct s_coordinates
{
	double x;
	double y;
	double z;
	double w;
}	t_coordinates;

typedef struct s_render
{
	t_mlx		*mlx;
	t_mlx_image	*image;
}	t_render;

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

typedef struct s_camera
{
	int				camera;
	t_coordinates	point;
	t_coordinates	vector;
	double			fov;
}	t_camera;

typedef struct s_light
{
	int				light;
	t_coordinates	point;
	double			brightness;
	t_color			color;
}	t_light;

typedef struct s_sphere
{
	t_coordinates	point;
	double			diameter;
	t_color			color;
}	t_sphere;

typedef struct s_plane
{
	t_coordinates	point;
	t_coordinates	vector;
	t_color			color;
}	t_plane;

typedef struct s_cylinder
{
	t_coordinates	point;
	t_coordinates	vector;
	double			diameter;
	double			heigh;
	t_color			color;
}	t_cylinder;

typedef struct s_rt
{
	t_amb_light	amb_light;
	t_camera	camera;
	t_render	render;
	t_light		light;
	t_sphere	*spheres;
	t_plane		*planes;
	t_cylinder	*cylinders;
	char		**linesread;
	char		**lineread;
	char		**color;
	char		**coordinates;
	int			num_sp;
	int			num_pl;
	int			num_cy;
}	t_rt;


#endif