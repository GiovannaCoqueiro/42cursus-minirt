/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ada-cruz <ada-cruz@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 00:26:06 by ada-cruz          #+#    #+#             */
/*   Updated: 2022/09/13 15:55:12 by ada-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	ldst;
	size_t	lsrc;

	i = 0;
	j = 0;
	ldst = ft_strlen(dst);
	lsrc = ft_strlen(src);
	if (size <= ldst)
		return (lsrc + size);
	while (dst[i] != '\0')
		i++;
	while ((i + 1) < size && src[j] != '\0')
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	dst[i] = '\0';
	return (ldst + lsrc);
}
