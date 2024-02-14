/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ada-cruz <ada-cruz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 16:42:15 by ada-cruz          #+#    #+#             */
/*   Updated: 2024/02/07 18:13:19 by ada-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	**create_translation_matrix(t_coordinates tuple)
{
	double	**translate_matrix;

	translate_matrix = creating_identity_matrix(4);
	translate_matrix[0][3] = tuple.x;
	translate_matrix[1][3] = tuple.y;
	translate_matrix[2][3] = tuple.z;
	return (translate_matrix);
}

double	**create_scaling_matrix(t_coordinates tuple)
{
	double	**scaling_matrix;

	scaling_matrix = creating_identity_matrix(4);
	scaling_matrix[0][0] = tuple.x;
	scaling_matrix[1][1] = tuple.y;
	scaling_matrix[2][2] = tuple.z;
	return (scaling_matrix);
}

double	**create_rotation_x_matrix(double degree)
{
	double	**rotation_x_matrix;
	double	rad;

	rad = degree_to_rad(degree);
	rotation_x_matrix = creating_identity_matrix(4);
	rotation_x_matrix[1][1] = cos(rad);
	rotation_x_matrix[1][2] = -sin(rad);
	rotation_x_matrix[2][1] = sin(rad);
	rotation_x_matrix[2][2] = cos(rad);
	return (rotation_x_matrix);
}

double	**create_rotation_y_matrix(double degree)
{
	double	**rotation_y_matrix;
	double	rad;

	rad = degree_to_rad(degree);
	rotation_y_matrix = creating_identity_matrix(4);
	rotation_y_matrix[0][0] = cos(rad);
	rotation_y_matrix[0][2] = sin(rad);
	rotation_y_matrix[2][0] = -sin(rad);
	rotation_y_matrix[2][2] = cos(rad);
	return (rotation_y_matrix);
}

double	**create_rotation_z_matrix(double degree)
{
	double	**rotation_z_matrix;
	double	rad;

	rad = degree_to_rad(degree);
	rotation_z_matrix = creating_identity_matrix(4);
	rotation_z_matrix[0][0] = cos(rad);
	rotation_z_matrix[0][1] = -sin(rad);
	rotation_z_matrix[1][0] = sin(rad);
	rotation_z_matrix[1][1] = cos(rad);
	return (rotation_z_matrix);
}
