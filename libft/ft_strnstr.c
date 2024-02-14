/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ada-cruz <ada-cruz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 01:20:41 by ada-cruz          #+#    #+#             */
/*   Updated: 2023/05/09 18:46:48 by ada-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (little == NULL || little[0] == '\0')
		return ((char *)big);
	if (len > ft_strlen(big))
		len = ft_strlen(big);
	while (i < len && big[i] != '\0')
	{
		j = 0;
		while ((big)[i] != (little)[j] && i < len)
			i++;
		while ((big)[i + j] == (little)[j] && i + j < len)
		{
			j++;
		}
		if (little[j] == '\0')
			return ((char *)big + i);
		i++;
	}
	return (NULL);
}
