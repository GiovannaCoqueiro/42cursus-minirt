/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_normal_vector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ada-cruz <ada-cruz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 16:41:37 by ada-cruz          #+#    #+#             */
/*   Updated: 2024/02/07 17:56:46 by ada-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_coordinates	normal_vector_sphere(t_sphere *sphere, t_coordinates w_point)
{
	t_coordinates	object_point;
	t_coordinates	object_normal;
	t_coordinates	world_normal;

	object_point = multiply_matrix_tuple(sphere->inverse_matrix, w_point);
	object_normal = subtract_tuples(object_point, create_point(0, 0, 0));
	world_normal = multiply_matrix_tuple(sphere->transpose_matrix,
			object_normal);
	world_normal.w = 0;
	normalize_vector(&world_normal);
	return (world_normal);
}

t_coordinates	normal_vector_cylinder(t_cylinder *cy, t_coordinates w_point)
{
	t_coordinates	object_point;
	t_coordinates	object_normal;
	t_coordinates	world_normal;
	double			t;

	object_point = multiply_matrix_tuple(cy->inverse_matrix, w_point);
	t = pow(object_point.x, 2) + pow(object_point.z, 2);
	if (t < 1 && are_equals(object_point.y, cy->max))
		object_normal = create_vector(0, 1, 0);
	else if (t < 1 && are_equals(object_point.y, cy->min))
		object_normal = create_vector(0, -1, 0);
	else
		object_normal = create_vector(object_point.x, 0, object_point.z);
	world_normal = multiply_matrix_tuple(cy->transpose_matrix, object_normal);
	world_normal.w = 0;
	normalize_vector(&world_normal);
	return (world_normal);
}

void	normal_object(t_intersections *temp)
{
	if (temp->object == SP)
		temp->normal = normal_vector_sphere(temp->sphere, temp->hit_point);
	if (temp->object == PL)
	{
		temp->normal = temp->plane->vector;
		normalize_vector(&temp->normal);
	}
	if (temp->object == CY)
		temp->normal = normal_vector_cylinder(temp->cylinder, temp->hit_point);
}
