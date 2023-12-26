/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ada-cruz <ada-cruz@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 14:49:41 by ada-cruz          #+#    #+#             */
/*   Updated: 2022/09/21 17:10:18 by ada-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	len;

	len = ft_strlen(s);
	if (s == NULL)
		return (NULL);
	while (s[len] != (unsigned char)c && len > 0)
	{
		len--;
	}
	if (s[len] == (unsigned char)c)
	{
		return ((char *)s + len);
	}
	return (NULL);
}
