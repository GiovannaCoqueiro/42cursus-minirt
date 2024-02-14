/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ada-cruz <ada-cruz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 16:41:30 by ada-cruz          #+#    #+#             */
/*   Updated: 2024/02/07 18:07:58 by ada-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_delta	delta_intersect_ray_cylinder(t_ray ray)
{
	t_delta	delta;
	double	temp;

	delta.a = pow(ray.direction.x, 2) + pow(ray.direction.z, 2);
	if (are_equals(delta.a, 0))
	{
		delta.delta = -1;
		return (delta);
	}
	delta.b = 2 * ray.origin.x * ray.direction.x + 2 \
		* ray.origin.z * ray.direction.z;
	delta.c = pow(ray.origin.x, 2) + pow(ray.origin.z, 2) - 1;
	delta.delta = pow(delta.b, 2) - (4 * delta.a * delta.c);
	delta.t[0] = (-delta.b - sqrt(delta.delta)) / (2 * delta.a);
	delta.t[1] = (-delta.b + sqrt(delta.delta)) / (2 * delta.a);
	if (delta.t[0] > delta.t[1])
	{
		temp = delta.t[0];
		delta.t[0] = delta.t[1];
		delta.t[1] = temp;
	}
	return (delta);
}

void	intersect_cylinder(t_rt *rt, t_ray ray, t_intersections **intersec)
{
	t_hit	hit;
	int		i;

	i = -1;
	while (++i < rt->num_cy)
	{
		hit = ray_cylinder_intersections(ray, &rt->cylinders[i]);
		if (hit.count != 0)
			add_intersection(intersec, hit, ray);
	}
}

void	cylinders_transformations(t_rt *rt)
{
	double	**scaling_translation;
	double	**rotation;
	double	**mult;
	double	r;
	int		i;

	i = -1;
	while (++i < rt->num_cy)
	{
		r = rt->cylinders[i].diameter / 2;
		scaling_translation = create_scaling_matrix(create_point(r, r, r));
		rotation = calculate_rotation(rt->cylinders[i].vector);
		mult = multiply_matrix(rotation, scaling_translation);
		free_matrix(rotation);
		free_matrix(scaling_translation);
		scaling_translation = create_translation_matrix(rt->cylinders[i].point);
		rotation = multiply_matrix(scaling_translation, mult);
		free_matrix(scaling_translation);
		free_matrix(mult);
		rt->cylinders[i].inverse_matrix = invert_matrix(rotation);
		rt->cylinders[i].transpose_matrix = \
			transposing_matrix(rt->cylinders[i].inverse_matrix);
		free_matrix(rotation);
	}
}

t_hit	ray_cylinder_intersections(t_ray ray, t_cylinder *cylinder)
{
	t_hit	hit;
	t_ray	new_ray;
	t_delta	delta;
	int		i;
	double	y;

	new_ray = ray_transformation(ray, cylinder->inverse_matrix);
	hit = (t_hit){CY, 0, .cylinder = cylinder, .ray = ray};
	hit.color = cylinder->color;
	delta = delta_intersect_ray_cylinder(new_ray);
	if (delta.delta >= -EPSILON)
	{
		i = -1;
		while (++i < 2)
		{
			y = new_ray.origin.y + delta.t[i] * new_ray.direction.y;
			if (y > cylinder->min && y < cylinder->max)
			{
				hit.t[hit.count] = delta.t[i];
				hit.hit_point[hit.count++] = find_position(ray, hit.t[i]);
			}
		}
	}
	intersect_cylinder_cap(new_ray, ray, cylinder, &hit);
	return (hit);
}
