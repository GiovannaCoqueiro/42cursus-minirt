/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_camera_and_lights.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ada-cruz <ada-cruz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 16:42:29 by ada-cruz          #+#    #+#             */
/*   Updated: 2024/02/07 16:42:30 by ada-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	validate_amb_light(t_rt *rt)
{
	if (rt->amb_light.amb_light)
		print_error("error in amb_light validation", rt);
	if (!rt->lineread[1] || !rt->lineread[2] || rt->lineread[3])
		print_error("error in amb_light validation", rt);
	if (!validate_double(rt->lineread[1]))
		print_error("error in amb_light validation", rt);
	rt->amb_light.ratio = ft_atod(rt->lineread[1]);
	if (rt->amb_light.ratio > 1 || rt->amb_light.ratio < 0)
		print_error("error in amb_light validation", rt);
	rt->color = ft_split(rt->lineread[2], ',');
	if (validate_color(rt->color) == 0)
		print_error("error in amb_light validation", rt);
	set_color(&rt->amb_light.color, rt->color);
	free_ptrptr(&rt->color);
	rt->amb_light.amb_light = 1;
}

static void	validate_camera(t_rt *rt)
{
	if (rt->camera.camera)
		print_error("error in camera validation", rt);
	if (!rt->lineread[1] || !rt->lineread[2] || !rt->lineread[3]
		|| rt->lineread[4])
		print_error("error in camera validation", rt);
	rt->coordinates = ft_split(rt->lineread[1], ',');
	if (validate_coordinates(rt->coordinates) == 0)
		print_error("error in camera validation", rt);
	set_coordinates(&rt->camera.point, rt->coordinates, POINT);
	free_ptrptr(&rt->coordinates);
	rt->coordinates = ft_split(rt->lineread[2], ',');
	if (!validate_coordinates(rt->coordinates))
		print_error("error in camera validation", rt);
	set_coordinates(&rt->camera.vector, rt->coordinates, VECTOR);
	if (!validate_normalized_vector(rt->camera.vector))
		print_error("the vector is not normalized", rt);
	free_ptrptr(&rt->coordinates);
	if (!validate_angle(rt->lineread[3]))
		print_error("error to validade the angle", rt);
	rt->camera.fov = ft_atod(rt->lineread[3]);
	rt->camera.camera = 1;
}

static void	validate_light(t_rt *rt)
{
	if (rt->light.light)
		print_error("error in light validation", rt);
	if (!rt->lineread[1] || !rt->lineread[2] || !rt->lineread[3]
		|| rt->lineread[4])
		print_error("error in light validation", rt);
	rt->coordinates = ft_split(rt->lineread[1], ',');
	if (!validate_coordinates(rt->coordinates))
		print_error("error in light's coordinates validation", rt);
	set_coordinates(&rt->light.point, rt->coordinates, POINT);
	free_ptrptr(&rt->coordinates);
	if (!validate_double(rt->lineread[2]))
		print_error("error in brightness ratio", rt);
	rt->light.brightness = ft_atod(rt->lineread[2]);
	if (rt->light.brightness > 1 || rt->light.brightness < 0)
		print_error("error in brightness range", rt);
	rt->color = ft_split(rt->lineread[3], ',');
	if (!validate_color(rt->color))
		print_error("error in light's color", rt);
	set_color(&rt->light.color, rt->color);
	free_ptrptr(&rt->color);
	rt->light.light = 1;
}

void	validate_elements(t_rt *rt)
{
	if (!ft_strncmp(rt->lineread[0], "A", 2))
		validate_amb_light(rt);
	else if (!ft_strncmp(rt->lineread[0], "C", 2))
		validate_camera(rt);
	else if (!ft_strncmp(rt->lineread[0], "L", 2))
		validate_light(rt);
	else if (!ft_strncmp(rt->lineread[0], "sp", 3))
		rt->num_sp++;
	else if (!ft_strncmp(rt->lineread[0], "pl", 3))
		rt->num_pl++;
	else if (!ft_strncmp(rt->lineread[0], "cy", 3))
		rt->num_cy++;
	else
		print_error("there is a wrong element or object in the file", rt);
}
