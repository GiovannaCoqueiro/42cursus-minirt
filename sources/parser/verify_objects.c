/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_objects.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcoqueir <gcoqueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 16:42:39 by ada-cruz          #+#    #+#             */
/*   Updated: 2024/02/08 07:55:40 by gcoqueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	validate_sphere(t_rt *rt, int sp)
{
	if (!rt->lineread[1] || !rt->lineread[2] || !rt->lineread[3] \
		|| rt->lineread[4])
		print_error("Error in sphere validation", rt);
	rt->coordinates = ft_split(rt->lineread[1], ',');
	if (!validate_coordinates(rt->coordinates))
		print_error("Error in sphere coordinates", rt);
	set_coordinates(&rt->sphere[sp].point, rt->coordinates, POINT);
	free_ptrptr(&rt->coordinates);
	if (!validate_double(rt->lineread[2]))
		print_error("Error in sphere diameter", rt);
	rt->sphere[sp].diameter = ft_atod(rt->lineread[2]);
	if (rt->sphere[sp].diameter <= EPSILON)
		print_error("The diameter is too little", rt);
	rt->color = ft_split(rt->lineread[3], ',');
	if (!validate_color(rt->color))
		print_error("Error in sphere color", rt);
	set_color(&rt->sphere[sp].color, rt->color);
	free_ptrptr(&rt->color);
}

void	validate_plane(t_rt *rt, int pl)
{
	if (!rt->lineread[1] || !rt->lineread[2] || !rt->lineread[3] \
		|| rt->lineread[4])
		print_error("Error in plane validation", rt);
	rt->coordinates = ft_split(rt->lineread[1], ',');
	if (!validate_coordinates(rt->coordinates))
		print_error("error in plane coordinates", rt);
	set_coordinates(&rt->planes[pl].point, rt->coordinates, POINT);
	free_ptrptr(&rt->coordinates);
	rt->coordinates = ft_split(rt->lineread[2], ',');
	if (!validate_coordinates(rt->coordinates))
		print_error("error in plane coordinates", rt);
	set_coordinates(&rt->planes[pl].vector, rt->coordinates, VECTOR);
	if (!validate_normalized_vector(rt->planes[pl].vector))
		print_error("the plane vector is not normalized", rt);
	free_ptrptr(&rt->coordinates);
	rt->color = ft_split(rt->lineread[3], ',');
	if (!validate_color(rt->color))
		print_error("error in plane color validation", rt);
	set_color(&rt->planes[pl].color, rt->color);
	free_ptrptr(&rt->color);
}

static void	validate_cylinder_aux(t_rt *rt, int cy)
{
	if (!validate_double(rt->lineread[4]))
		print_error("error in cylinder height", rt);
	rt->cylinders[cy].height = ft_atod(rt->lineread[4]);
	if (rt->cylinders[cy].height <= EPSILON)
		print_error("Error in cylinder height", rt);
	rt->cylinders[cy].max = rt->cylinders[cy].height / 2;
	rt->cylinders[cy].min = -rt->cylinders[cy].max;
	rt->color = ft_split(rt->lineread[5], ',');
	if (!validate_color(rt->color))
		print_error("Error in cylinder color", rt);
	set_color(&rt->cylinders[cy].color, rt->color);
	free_ptrptr(&rt->color);
}

void	validate_cylinder(t_rt *rt, int cy)
{
	if (!rt->lineread[1] || !rt->lineread[2] || !rt->lineread[3] \
		|| !rt->lineread[4] || !rt->lineread[5] || rt->lineread[6])
		print_error("error in cylinder validation", rt);
	rt->coordinates = ft_split(rt->lineread[1], ',');
	if (!validate_coordinates(rt->coordinates))
		print_error("error in cylinder coordinates", rt);
	set_coordinates(&rt->cylinders[cy].point, rt->coordinates, POINT);
	free_ptrptr(&rt->coordinates);
	rt->coordinates = ft_split(rt->lineread[2], ',');
	if (!validate_coordinates(rt->coordinates))
		print_error("error in cylinder coordinates", rt);
	set_coordinates(&rt->cylinders[cy].vector, rt->coordinates, VECTOR);
	if (!validate_normalized_vector(rt->cylinders[cy].vector))
		print_error("the cylinders vector is not normalized", rt);
	free_ptrptr(&rt->coordinates);
	if (!validate_double(rt->lineread[3]))
		print_error("error in cylinder diameter", rt);
	rt->cylinders[cy].diameter = ft_atod(rt->lineread[3]);
	if (rt->cylinders[cy].diameter <= EPSILON)
		print_error("Error in cylinder diamter", rt);
	validate_cylinder_aux(rt, cy);
}
