/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcoqueir <gcoqueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 16:41:40 by ada-cruz          #+#    #+#             */
/*   Updated: 2024/02/08 14:45:39 by gcoqueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_intersections	*new_intersec(t_ray ray, int i, t_hit new)
{
	t_intersections	*temp;

	temp = ft_calloc(1, sizeof(t_intersections));
	if (temp == NULL)
		return (NULL);
	temp->object = new.object;
	temp->t = new.t[i];
	temp->hit_point = new.hit_point[i];
	temp->color = new.color;
	temp->eye = eye_vector(ray.direction);
	temp->inside = 0;
	if (new.object == SP)
		temp->sphere = new.sphere;
	if (new.object == PL)
		temp->plane = new.plane;
	if (new.object == CY)
		temp->cylinder = new.cylinder;
	normal_object(temp);
	if (dot_product(temp->normal, temp->eye) < 0)
		temp->normal = negate_tuples(temp->normal);
	temp->over_point = adding_tuples(temp->hit_point, multiply_tuples(EPSILON,
				temp->normal));
	temp->next = NULL;
	return (temp);
}

void	list_intersec_position(t_intersections **intersec, t_intersections *new)
{
	t_intersections	*temp;
	t_intersections	*temp_next;

	if (*intersec == NULL || (*intersec)->t > new->t)
	{
		new->next = *intersec;
		*intersec = new;
		return ;
	}
	temp = *intersec;
	while (temp->next && temp->next->t <= new->t)
		temp = temp->next;
	temp_next = temp->next;
	temp->next = new;
	new->next = temp_next;
}

void	add_intersection(t_intersections **intersec, t_hit new, t_ray ray)
{
	int	i;

	i = -1;
	while (++i < new.count)
		list_intersec_position(intersec, new_intersec(ray, i, new));
}

void	get_intersections(t_rt *rt, t_intersections **intersections, t_ray ray)
{
	if (rt->num_sp != 0)
		intersect_sphere(rt, ray, intersections);
	if (rt->num_pl != 0)
		intersect_plane(rt, ray, intersections);
	if (rt->num_cy != 0)
		intersect_cylinder(rt, ray, intersections);
}

t_intersections	*hit_point(t_intersections **intersec)
{
	t_intersections	*temp;

	temp = *intersec;
	while (temp)
	{
		if (temp->t > 0)
			break ;
		temp = temp->next;
	}
	return (temp);
}
