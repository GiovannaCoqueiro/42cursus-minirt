/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ada-cruz <ada-cruz@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 19:17:01 by ada-cruz          #+#    #+#             */
/*   Updated: 2022/09/20 23:31:56 by ada-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	int		position;
	int		lenght;
	char	*dest;

	lenght = 0;
	while (s[lenght] != '\0')
		lenght++;
	dest = (char *)malloc(sizeof(char) * (lenght + 1));
	position = 0;
	while (position < lenght)
	{
		dest[position] = s[position];
		position++;
	}
	dest[position] = '\0';
	return (dest);
}
