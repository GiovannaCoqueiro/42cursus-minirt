/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tuples.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ada-cruz <ada-cruz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 16:42:54 by ada-cruz          #+#    #+#             */
/*   Updated: 2024/02/07 16:42:55 by ada-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_coordinates	create_point(double x, double y, double z)
{
	t_coordinates	tuple_point;

	tuple_point.x = x;
	tuple_point.y = y;
	tuple_point.z = z;
	tuple_point.w = 1;
	return (tuple_point);
}

t_coordinates	create_vector(double x, double y, double z)
{
	t_coordinates	tuple_vector;

	tuple_vector.x = x;
	tuple_vector.y = y;
	tuple_vector.z = z;
	tuple_vector.w = 0;
	return (tuple_vector);
}
