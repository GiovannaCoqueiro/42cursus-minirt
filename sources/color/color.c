/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcoqueir <gcoqueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 16:38:09 by gcoqueir          #+#    #+#             */
/*   Updated: 2024/02/07 16:38:30 by gcoqueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	adding_colors(t_color a, t_color b)
{
	t_color	new_color;

	new_color.red = a.red + b.red;
	if (new_color.red > 255)
		new_color.red = 255;
	new_color.green = a.green + b.green;
	if (new_color.green > 255)
		new_color.green = 255;
	new_color.blue = a.blue + b.blue;
	if (new_color.blue > 255)
		new_color.blue = 255;
	return (new_color);
}

t_color	subtract_colors(t_color a, t_color b)
{
	t_color	new_color;

	new_color.red = a.red - b.red;
	if (new_color.red < 0)
		new_color.red = 0;
	new_color.green = a.green - b.green;
	if (new_color.green < 0)
		new_color.green = 0;
	new_color.blue = a.blue - b.blue;
	if (new_color.blue < 0)
		new_color.blue = 0;
	return (new_color);
}

t_color	multiply_color_by_scalar(t_color material, double scalar)
{
	t_color	new_color;

	if (scalar > 1)
		scalar = 1;
	if (scalar < 0)
		scalar = 0;
	new_color.blue = material.blue * scalar;
	new_color.green = material.green * scalar;
	new_color.red = material.red * scalar;
	return (new_color);
}

t_color	multiply_colors(t_color a, t_color b)
{
	t_color	new_color;

	new_color.blue = a.blue * b.blue / 255;
	new_color.green = a.green * b.green / 255;
	new_color.red = a.red * b.red / 255;
	return (new_color);
}
