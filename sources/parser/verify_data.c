/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ada-cruz <ada-cruz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 16:42:33 by ada-cruz          #+#    #+#             */
/*   Updated: 2024/02/07 16:42:34 by ada-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	validate_normalized_vector(t_coordinates coordinates)
{
	return (are_equals(calculate_vector_magnitude(coordinates), 1));
}

int	validate_angle(char *angle)
{
	return (angle && validate_double(angle) && ft_atod(angle) >= 0
		&& ft_atod(angle) <= 180);
}

int	validate_color(char **color)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while (color && color[i] && validate_int(color[i]) == 0)
	{
		if (ft_atoi(color[i]) < 0 || ft_atoi(color[i]) > 255)
			break ;
		i++;
	}
	if (i != 3)
		return (0);
	return (1);
}

int	validate_coordinates(char **coordinates)
{
	int	i;

	i = 0;
	while (coordinates && coordinates[i] && validate_double(coordinates[i]))
		i++;
	if (i != 3)
		return (0);
	return (1);
}
