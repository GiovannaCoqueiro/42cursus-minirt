/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcoqueir <gcoqueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 16:42:44 by ada-cruz          #+#    #+#             */
/*   Updated: 2024/02/08 15:40:14 by gcoqueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	is_shadowed(t_rt *rt, t_coordinates point)
{
	t_coordinates	vector;
	double			distance;
	t_ray			ray;
	t_intersections	*intersections;
	t_intersections	*new_hit;

	vector = subtract_tuples(rt->light.point, point);
	distance = calculate_vector_magnitude(vector);
	normalize_vector(&vector);
	ray = create_ray(point, vector);
	intersections = NULL;
	get_intersections(rt, &intersections, ray);
	new_hit = hit_point(&intersections);
	if (new_hit != NULL && new_hit->t < distance)
	{
		free_intersections(&intersections);
		return (1);
	}
	free_intersections(&intersections);
	return (0);
}

static t_color	calculate_diffuse(t_rt *rt, t_intersections *hit, \
	t_color ef_color)
{
	double			light_dot_normal;
	t_coordinates	light_v;

	light_v = subtract_tuples(rt->light.point, hit->hit_point);
	normalize_vector(&light_v);
	light_dot_normal = dot_product(light_v, hit->normal);
	if (light_dot_normal < 0)
		return ((t_color){0, 0, 0});
	else
		return (multiply_color_by_scalar(ef_color, rt->material->diffuse \
			* light_dot_normal));
}

static t_color	calculate_specular(t_rt *rt, t_intersections *hit)
{
	double			light_dot_normal;
	double			reflect_dot_eye;
	t_coordinates	light_v;
	t_coordinates	reflect_v;
	double			factor;

	light_v = subtract_tuples(rt->light.point, hit->hit_point);
	normalize_vector(&light_v);
	light_dot_normal = dot_product(light_v, hit->normal);
	if (light_dot_normal < 0)
		return ((t_color){0, 0, 0});
	reflect_v = reflect_vector(negate_tuples(light_v), hit->normal);
	reflect_dot_eye = dot_product(reflect_v, hit->eye);
	if (reflect_dot_eye <= 0)
		return ((t_color){0, 0, 0});
	else
	{
		factor = pow(reflect_dot_eye, rt->material->shininess);
		return (multiply_color_by_scalar \
			(multiply_color_by_scalar((t_color){255, 255, 255}, \
			rt->light.brightness), rt->material->specular * factor));
	}
}

t_color	intensity(t_rt *rt, t_intersections *hit, int is_shadowed)
{
	t_color	ef_color;
	t_color	ambient;
	t_color	diffuse;
	t_color	specular;
	t_color	aux_color;

	ef_color = multiply_colors(hit->color, \
		multiply_color_by_scalar(((t_color){255, 255, 255}), \
		rt->light.brightness));
	ambient = multiply_color_by_scalar(hit->color, rt->material->ambient);
	diffuse = calculate_diffuse(rt, hit, ef_color);
	specular = calculate_specular(rt, hit);
	aux_color = (t_color){0, 0, 0};
	aux_color = adding_colors(specular, \
		adding_colors(multiply_color_by_scalar(ef_color, \
		rt->material->ambient), multiply_colors(hit->color, \
		multiply_color_by_scalar(rt->amb_light.color, rt->amb_light.ratio))));
	if (is_shadowed != 1)
		aux_color = adding_colors(aux_color, diffuse);
	return (aux_color);
}

t_color	result_color(t_rt *rt, t_ray ray)
{
	t_intersections	*intersections;
	t_color			color;
	t_intersections	*hit;
	int				is_shadow;

	color = (t_color){0, 0, 0};
	intersections = NULL;
	get_intersections(rt, &intersections, ray);
	hit = hit_point(&intersections);
	if (hit != NULL)
	{
		is_shadow = is_shadowed(rt, hit->over_point);
		color = intensity(rt, hit, is_shadow);
	}
	free_intersections(&intersections);
	return (color);
}
