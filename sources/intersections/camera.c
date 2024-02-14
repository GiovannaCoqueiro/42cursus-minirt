/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ada-cruz <ada-cruz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 16:40:50 by ada-cruz          #+#    #+#             */
/*   Updated: 2024/02/07 18:10:53 by ada-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	view_transformation(t_rt *rt, t_coordinates up)
{
	t_coordinates	left;
	t_coordinates	true_up;
	double			**orientation;
	double			**translation;

	left = cross_product(rt->camera.vector, up);
	true_up = cross_product(left, rt->camera.vector);
	orientation = creating_identity_matrix(4);
	orientation[0][0] = left.x;
	orientation[0][1] = left.y;
	orientation[0][2] = left.z;
	orientation[1][0] = true_up.x;
	orientation[1][1] = true_up.y;
	orientation[1][2] = true_up.z;
	orientation[2][0] = -rt->camera.vector.x;
	orientation[2][1] = -rt->camera.vector.y;
	orientation[2][2] = -rt->camera.vector.z;
	translation = create_translation_matrix(negate_tuples(rt->camera.point));
	rt->camera.trans_matrix = multiply_matrix(orientation, translation);
	rt->camera.invert_matrix = invert_matrix(rt->camera.trans_matrix);
	free_matrix(orientation);
	free_matrix(translation);
}

void	aux_view_transformation(t_rt *rt)
{
	t_coordinates	up;

	up = create_vector(0, 1, 0);
	if (are_equals(dot_product(rt->camera.vector, up), 1))
		up = create_vector(1, 0, 0);
	if (are_equals(dot_product(rt->camera.vector, up), -1))
		up = create_vector(-1, 0, 0);
	view_transformation(rt, up);
}

t_ray	ray_for_pixel(t_rt *rt, double x, double y)
{
	double			world_x;
	double			world_y;
	t_coordinates	direction;
	t_coordinates	pixel;
	t_coordinates	origin;

	world_x = rt->half_width - rt->pixel_size * (x + 0.5);
	world_y = rt->half_height - rt->pixel_size * (y + 0.5);
	pixel = multiply_matrix_tuple(rt->camera.invert_matrix,
			create_point(world_x, world_y, -1));
	origin = multiply_matrix_tuple(rt->camera.invert_matrix, create_point(0, 0,
				0));
	direction = subtract_tuples(pixel, origin);
	normalize_vector(&direction);
	return (create_ray(origin, direction));
}
