/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ada-cruz <ada-cruz@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 16:08:08 by ada-cruz          #+#    #+#             */
/*   Updated: 2022/09/20 01:14:49 by ada-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	char	*nwstr;

	i = 0;
	nwstr = (char *)ft_calloc(ft_strlen(s) + 1, sizeof(char));
	if (!nwstr)
		return (NULL);
	while (s[i] != '\0')
	{
		nwstr[i] = f(i, s[i]);
		i++;
	}
	return (nwstr);
}
