/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ada-cruz <ada-cruz@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 22:20:37 by ada-cruz          #+#    #+#             */
/*   Updated: 2022/09/09 01:08:49 by ada-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((s1[i] || s2[i]) && (i < n))
	{
		if (((unsigned char) s1[i]) < ((unsigned char) s2[i]))
			return (-1);
		if (((unsigned char) s1[i]) > ((unsigned char) s2[i]))
			return (1);
		i++;
	}
	return (0);
}
