/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcoqueir <gcoqueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 16:42:47 by ada-cruz          #+#    #+#             */
/*   Updated: 2024/02/08 14:58:46 by gcoqueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	render(t_rt *rt)
{
	int		y;
	int		x;
	t_ray	ray;
	t_color	color;
	char	*pixel;

	set_mlx(rt);
	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			ray = ray_for_pixel(rt, x, y);
			color = result_color(rt, ray);
			pixel = rt->mlx.addr + (y * rt->mlx.line_length + x \
				* (rt->mlx.bits_per_pixel / 8));
			*(int *)pixel = color.red << 16 | color.green << 8 | color.blue;
		}
	}
	mlx_put_image_to_window(rt->mlx.mlx, rt->mlx.window, rt->mlx.image, 0, 0);
}

static int	x_press(t_rt *rt)
{
	if (rt != NULL)
		free_rt(rt);
	return (1);
}

static int	key_pressed(int key, t_rt *rt)
{
	if (key == XK_Escape)
		x_press(rt);
	return (1);
}

void	minirt(t_rt *rt)
{
	mlx_key_hook(rt->mlx.window, key_pressed, rt);
	mlx_hook(rt->mlx.window, DestroyNotify, NoEventMask, x_press, rt);
	mlx_loop(rt->mlx.mlx);
}
