/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_numbers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ada-cruz <ada-cruz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 16:42:36 by ada-cruz          #+#    #+#             */
/*   Updated: 2024/02/07 16:42:37 by ada-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	validate_double(char *number)
{
	int	i;

	i = 0;
	if (!number || !number[i])
		return (0);
	if (number[i] == '+' || number[i] == '-')
		i++;
	if (!number[i])
		return (0);
	while (ft_isdigit(number[i]))
		i++;
	if (!number[i])
		return (1);
	if (number[i] == '.')
		i++;
	if (!number[i])
		return (0);
	while (ft_isdigit(number[i]))
		i++;
	if (!number[i])
		return (1);
	return (0);
}

int	validate_int(char *number)
{
	int	i;

	i = 0;
	if (!number || !number[i] || ft_strlen(number) > 3)
		return (0);
	while (ft_isdigit(number[i]))
		i++;
	if (!number[i])
		return (0);
	return (1);
}
