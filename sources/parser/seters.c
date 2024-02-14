/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   seters.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ada-cruz <ada-cruz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 16:42:26 by ada-cruz          #+#    #+#             */
/*   Updated: 2024/02/07 16:42:27 by ada-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	set_coordinates(t_coordinates *dest, char **src, double w)
{
	(*dest).x = ft_atod(src[0]);
	(*dest).y = ft_atod(src[1]);
	(*dest).z = ft_atod(src[2]);
	(*dest).w = w;
}

void	set_color(t_color *dest, char **src)
{
	(*dest).red = ft_atoi(src[0]);
	(*dest).green = ft_atoi(src[1]);
	(*dest).blue = ft_atoi(src[2]);
}
