/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ada-cruz <ada-cruz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 16:41:58 by ada-cruz          #+#    #+#             */
/*   Updated: 2024/02/07 16:50:41 by ada-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_delta	delta_intersect_ray_sphere(t_ray ray)
{
	t_delta	delta;

	delta.object_to_ray = subtract_tuples(ray.origin, create_point(0, 0, 0));
	delta.a = dot_product(ray.direction, ray.direction);
	delta.b = 2 * dot_product(ray.direction, delta.object_to_ray);
	delta.c = dot_product(delta.object_to_ray, delta.object_to_ray) - 1;
	delta.delta = pow(delta.b, 2) - (4 * delta.a * delta.c);
	delta.t[0] = (-delta.b - sqrt(delta.delta)) / (2 * delta.a);
	delta.t[1] = (-delta.b + sqrt(delta.delta)) / (2 * delta.a);
	return (delta);
}

void	intersect_sphere(t_rt *rt, t_ray ray, t_intersections **intersec)
{
	t_hit	hit;
	int		i;

	i = -1;
	while (++i < rt->num_sp)
	{
		hit = ray_sphere_intersections(ray, &rt->sphere[i]);
		if (hit.count != 0)
			add_intersection(intersec, hit, ray);
	}
}

void	spheres_transformations(t_rt *rt)
{
	double	**translation;
	double	**scaling;
	double	**mult;
	double	r;
	int		i;

	i = -1;
	while (++i < rt->num_sp)
	{
		r = rt->sphere[i].diameter / 2;
		scaling = create_scaling_matrix((t_coordinates){r, r, r, 1});
		translation = create_translation_matrix(rt->sphere[i].point);
		mult = multiply_matrix(translation, scaling);
		rt->sphere[i].inverse_matrix = invert_matrix(mult);
		rt->sphere[i].transpose_matrix = \
			transposing_matrix(rt->sphere[i].inverse_matrix);
		free_matrix(translation);
		free_matrix(scaling);
		free_matrix(mult);
	}
}

t_hit	ray_sphere_intersections(t_ray ray, t_sphere *sphere)
{
	t_hit	hit;
	t_ray	new_ray;
	t_delta	delta;

	new_ray = ray_transformation(ray, sphere->inverse_matrix);
	hit.object = SP;
	hit.count = 0;
	hit.sphere = sphere;
	hit.ray = ray;
	hit.color = sphere->color;
	delta = delta_intersect_ray_sphere(new_ray);
	if (delta.delta < 0)
		return (hit);
	hit.t[0] = delta.t[0];
	hit.hit_point[0] = find_position(ray, hit.t[0]);
	if (are_equals(delta.delta, 0))
		hit.count = 1;
	else
	{
		hit.count = 2;
		hit.t[1] = delta.t[1];
		hit.hit_point[1] = find_position(ray, hit.t[1]);
	}
	return (hit);
}
