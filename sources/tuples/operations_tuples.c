/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_tuples.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ada-cruz <ada-cruz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 16:42:57 by ada-cruz          #+#    #+#             */
/*   Updated: 2024/02/07 16:42:58 by ada-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_coordinates	adding_tuples(t_coordinates a, t_coordinates b)
{
	t_coordinates	new_tuple;

	new_tuple.x = a.x + b.x;
	new_tuple.y = a.y + b.y;
	new_tuple.z = a.z + b.z;
	new_tuple.w = a.w + b.w;
	return (new_tuple);
}

t_coordinates	subtract_tuples(t_coordinates a, t_coordinates b)
{
	t_coordinates	new_tuple;

	new_tuple.x = a.x - b.x;
	new_tuple.y = a.y - b.y;
	new_tuple.z = a.z - b.z;
	new_tuple.w = a.w - b.w;
	return (new_tuple);
}

t_coordinates	multiply_tuples(double scalar, t_coordinates a)
{
	t_coordinates	new_tuple;

	new_tuple.x = scalar * a.x;
	new_tuple.y = scalar * a.y;
	new_tuple.z = scalar * a.z;
	new_tuple.w = scalar * a.w;
	return (new_tuple);
}

t_coordinates	divide_tuples(double scalar, t_coordinates a)
{
	t_coordinates	new_tuple;

	new_tuple.x = a.x / scalar;
	new_tuple.y = a.y / scalar;
	new_tuple.z = a.z / scalar;
	new_tuple.w = a.w / scalar;
	return (new_tuple);
}

t_coordinates	negate_tuples(t_coordinates a)
{
	t_coordinates	new_tuple;

	new_tuple.x = -1 * a.x;
	new_tuple.y = -1 * a.y;
	new_tuple.z = -1 * a.z;
	new_tuple.w = -1 * a.w;
	return (new_tuple);
}
