/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   are_equals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ada-cruz <ada-cruz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 16:42:51 by ada-cruz          #+#    #+#             */
/*   Updated: 2024/02/07 16:42:52 by ada-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	are_equals(double a, double b)
{
	if (fabs(a - b) < EPSILON)
		return (1);
	return (0);
}

int	are_equals_tuple(t_coordinates a, t_coordinates b)
{
	if (are_equals(a.x, b.x) && are_equals(a.y, b.y) && are_equals(a.z, b.z)
		&& are_equals(a.w, b.w))
		return (1);
	else
		return (0);
}
