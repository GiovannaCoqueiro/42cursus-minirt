/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformation_rotation.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ada-cruz <ada-cruz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 16:42:12 by ada-cruz          #+#    #+#             */
/*   Updated: 2024/02/07 18:13:13 by ada-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	**calculate_z_y_rotation_matrix(t_coordinates vector)
{
	double	**zrotation;
	double	**yrotation;
	double	**rotation;

	zrotation = create_rotation_z_matrix(-90);
	yrotation = create_rotation_y_matrix(atan(-vector.x / vector.z) \
		* (180 / M_PI));
	rotation = multiply_matrix(yrotation, zrotation);
	free_matrix(zrotation);
	free_matrix(yrotation);
	return (rotation);
}

double	**calculate_z_x_rotation_matrix(t_coordinates vector)
{
	double	**xrotation;
	double	**zrotation;
	double	**rotation;

	xrotation = create_rotation_x_matrix(atan(-vector.z / vector.y) \
		* (180 / M_PI));
	zrotation = create_rotation_z_matrix(atan(-vector.x / vector.y) \
		* (180 / M_PI));
	rotation = multiply_matrix(zrotation, xrotation);
	free_matrix(xrotation);
	free_matrix(zrotation);
	return (rotation);
}

double	**calculate_rotation(t_coordinates vector)
{
	double	**new_vector;

	if (are_equals_tuple(vector, create_vector(0, 1, 0)))
		new_vector = creating_identity_matrix(4);
	else if (are_equals_tuple(vector, create_vector(0, -1, 0)))
		new_vector = create_rotation_x_matrix(180);
	else if (are_equals_tuple(vector, create_vector(1, 0, 0)))
		new_vector = create_rotation_z_matrix(-90);
	else if (are_equals_tuple(vector, create_vector(-1, 0, 0)))
		new_vector = create_rotation_z_matrix(90);
	else if (are_equals_tuple(vector, create_vector(0, 0, 1)))
		new_vector = create_rotation_x_matrix(90);
	else if (are_equals_tuple(vector, create_vector(0, 0, -1)))
		new_vector = create_rotation_x_matrix(-90);
	else if (are_equals(vector.y, 0))
		new_vector = calculate_z_y_rotation_matrix(vector);
	else
		new_vector = calculate_z_x_rotation_matrix(vector);
	return (new_vector);
}
