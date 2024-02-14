/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_cap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ada-cruz <ada-cruz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 16:37:54 by gcoqueir          #+#    #+#             */
/*   Updated: 2024/02/07 18:09:47 by ada-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static double	check_cap(t_ray ray, double t)
{
	double	x;
	double	z;

	x = ray.origin.x + t * ray.direction.x;
	z = ray.origin.z + t * ray.direction.z;
	if (pow(x, 2) + pow(z, 2) <= 1 + EPSILON)
		return (1);
	return (0);
}

void	intersect_cylinder_cap(t_ray new_ray, t_ray old_ray, \
	t_cylinder *cylinder, t_hit *hit)
{
	double	t[2];

	if (are_equals(new_ray.direction.y, 0))
		return ;
	t[0] = (cylinder->min - new_ray.origin.y) / new_ray.direction.y;
	t[1] = (cylinder->max - new_ray.origin.y) / new_ray.direction.y;
	if (check_cap(new_ray, t[0]))
	{
		hit->t[hit->count] = t[0];
		hit->hit_point[hit->count] = find_position(old_ray, hit->t[0]);
		hit->count++;
	}
	if (check_cap(new_ray, t[1]))
	{
		hit->t[hit->count] = t[1];
		hit->hit_point[hit->count] = find_position(old_ray, hit->t[1]);
		hit->count++;
	}
}
