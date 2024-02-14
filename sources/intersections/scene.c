/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ada-cruz <ada-cruz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 16:41:55 by ada-cruz          #+#    #+#             */
/*   Updated: 2024/02/07 16:41:56 by ada-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_coordinates	eye_vector(t_coordinates vector)
{
	t_coordinates	eye;

	eye = negate_tuples(vector);
	return (eye);
}

t_coordinates	reflect_vector(t_coordinates in, t_coordinates normal)
{
	t_coordinates	new_coor;

	new_coor = subtract_tuples(in, multiply_tuples(dot_product(in, normal) * 2,
				normal));
	return (new_coor);
}

t_coordinates	light_vector(t_coordinates vector, t_coordinates point)
{
	t_coordinates	light;

	light = subtract_tuples(vector, point);
	return (light);
}
