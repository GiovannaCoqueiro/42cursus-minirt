/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ada-cruz <ada-cruz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 16:41:43 by ada-cruz          #+#    #+#             */
/*   Updated: 2024/02/07 16:48:14 by ada-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	intersect_plane(t_rt *rt, t_ray ray, t_intersections **intersec)
{
	t_hit	hit;
	int		i;

	i = -1;
	while (++i < rt->num_pl)
	{
		hit = ray_plane_intersections(ray, &rt->planes[i]);
		if (hit.count != 0)
			add_intersection(intersec, hit, ray);
	}
}

t_hit	ray_plane_intersections(t_ray ray, t_plane *plane)
{
	t_hit	hit;
	t_ray	new_ray;

	new_ray = ray_transformation(ray, plane->inverse_matrix);
	hit.object = PL;
	hit.count = 0;
	hit.plane = plane;
	hit.ray = ray;
	hit.color = plane->color;
	if (are_equals(new_ray.direction.y, 0))
		return (hit);
	hit.count = 1;
	hit.t[0] = -new_ray.origin.y / new_ray.direction.y;
	hit.hit_point[0] = find_position(ray, hit.t[0]);
	return (hit);
}

void	planes_transformations(t_rt *rt)
{
	double	**translation;
	double	**rotation;
	double	**mult;
	int		i;

	i = -1;
	while (++i < rt->num_pl)
	{
		rotation = calculate_rotation(rt->planes[i].vector);
		translation = create_translation_matrix(rt->planes[i].point);
		mult = multiply_matrix(translation, rotation);
		rt->planes[i].inverse_matrix = invert_matrix(mult);
		rt->planes[i].transpose_matrix = \
			transposing_matrix(rt->planes[i].inverse_matrix);
		free_matrix(translation);
		free_matrix(rotation);
		free_matrix(mult);
	}
}
