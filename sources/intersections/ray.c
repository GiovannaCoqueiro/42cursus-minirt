/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ada-cruz <ada-cruz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 16:41:49 by ada-cruz          #+#    #+#             */
/*   Updated: 2024/02/07 16:41:50 by ada-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_ray	create_ray(t_coordinates point, t_coordinates vector)
{
	t_ray	ray;

	ray.origin = point;
	ray.direction = vector;
	return (ray);
}

t_coordinates	find_position(t_ray ray, double t)
{
	t_coordinates	new_coor;

	new_coor = adding_tuples(ray.origin, multiply_tuples(t, ray.direction));
	return (new_coor);
}

t_ray	ray_transformation(t_ray ray, double **matrix)
{
	t_ray	new_ray;

	new_ray.origin = multiply_matrix_tuple(matrix, ray.origin);
	new_ray.direction = multiply_matrix_tuple(matrix, ray.direction);
	return (new_ray);
}
