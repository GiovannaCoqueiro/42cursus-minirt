/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_vector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ada-cruz <ada-cruz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 16:43:00 by ada-cruz          #+#    #+#             */
/*   Updated: 2024/02/07 16:43:01 by ada-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	calculate_vector_magnitude(t_coordinates v)
{
	double	magnitude;

	magnitude = sqrt(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2) + pow(v.w, 2));
	return (magnitude);
}

void	normalize_vector(t_coordinates *coordinates)
{
	double	magnitude;

	magnitude = calculate_vector_magnitude(*coordinates);
	coordinates->x = coordinates->x / magnitude;
	coordinates->y = coordinates->y / magnitude;
	coordinates->z = coordinates->z / magnitude;
	coordinates->w = coordinates->w / magnitude;
}

double	dot_product(t_coordinates a, t_coordinates b)
{
	double	new_coor;

	new_coor = a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
	return (new_coor);
}

t_coordinates	cross_product(t_coordinates a, t_coordinates b)
{
	t_coordinates	new_coor;

	new_coor.x = a.y * b.z - a.z * b.y;
	new_coor.y = a.z * b.x - a.x * b.z;
	new_coor.z = a.x * b.y - a.y * b.x;
	new_coor.w = 0.0;
	return (new_coor);
}
