/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ada-cruz <ada-cruz@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 16:27:33 by ada-cruz          #+#    #+#             */
/*   Updated: 2022/09/20 01:15:47 by ada-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_s1pluss2(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	size_t	s12_len;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	s12_len = (s1_len + s2_len);
	return (s12_len);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*substr;

	i = 0;
	substr = (char *)ft_calloc(ft_s1pluss2(s1, s2) + 1, sizeof(char));
	if (!substr)
		return (NULL);
	while (s1[i] != '\0')
	{
		substr[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0')
	{
		substr[i] = s2[j];
		i++;
		j++;
	}
	return (substr);
}
