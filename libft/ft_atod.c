/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ada-cruz <ada-cruz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 14:03:00 by ada-cruz          #+#    #+#             */
/*   Updated: 2023/10/10 14:03:11 by ada-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static double	ft_atod_decimal(const char *nptr)
{
	double	num;
	double	pow;

	num = 0;
	pow = 0.1;
	while (ft_isdigit(*nptr))
	{
		num = num + (*nptr - 48) * pow;
		pow /= 10;
		nptr++;
	}
	return (num);
}

double	ft_atod(const char *nptr)
{
	int		sign;
	double	num;

	sign = 1;
	while (ft_iswhitespace(*nptr))
		nptr++;
	if (*nptr == '-')
	{
		sign = -1;
		nptr++;
	}
	else if (*nptr == '+')
		nptr++;
	num = 0;
	while (ft_isdigit(*nptr))
	{
		num = num * 10 + (*nptr - 48);
		nptr++;
	}
	if (*nptr == '.')
		nptr++;
	num += ft_atod_decimal(nptr);
	return (num * sign);
}
