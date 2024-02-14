/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcoqueir <gcoqueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 16:40:46 by ada-cruz          #+#    #+#             */
/*   Updated: 2024/02/08 15:42:47 by gcoqueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_rt	*init_rt(void)
{
	t_rt	*rt;

	rt = ft_calloc(sizeof(t_rt), 1);
	rt->material = ft_calloc(sizeof(t_material), 1);
	set_material(rt->material);
	return (rt);
}

void	set_material(t_material *material)
{
	material->ambient = 0.1;
	material->diffuse = 0.9;
	material->specular = 0.9;
	material->shininess = 200.0;
}

void	set_transformations(t_rt *rt)
{
	spheres_transformations(rt);
	planes_transformations(rt);
	cylinders_transformations(rt);
}

void	set_mlx(t_rt *rt)
{
	rt->mlx.mlx = mlx_init();
	if (!rt->mlx.mlx)
		print_error("Problem initializing mlx pointer", rt);
	rt->mlx.window = mlx_new_window(rt->mlx.mlx, WIDTH, HEIGHT, "MiniRT");
	if (!rt->mlx.window)
		print_error("Problem initializing mlx window", rt);
	rt->mlx.image = mlx_new_image(rt->mlx.mlx, WIDTH, HEIGHT);
	if (!rt->mlx.image)
	{
		mlx_destroy_window(rt->mlx.mlx, rt->mlx.window);
		print_error("Problem initializing image pointer", rt);
	}
	rt->mlx.addr = mlx_get_data_addr(rt->mlx.image, &rt->mlx.bits_per_pixel,
			&rt->mlx.line_length, &rt->mlx.endian);
}

void	set_pixel_size(t_rt *rt)
{
	double	half_view;
	double	aspect;

	half_view = tan(degree_to_rad(rt->camera.fov) / 2);
	aspect = WIDTH / HEIGHT;
	if (aspect >= 1 - EPSILON)
	{
		rt->half_width = half_view;
		rt->half_height = half_view / aspect;
		rt->pixel_size = rt->half_width * 2 / WIDTH;
	}
	else
	{
		rt->half_width = half_view * aspect;
		rt->half_height = half_view;
		rt->pixel_size = rt->half_width * 2 / HEIGHT;
	}
}
