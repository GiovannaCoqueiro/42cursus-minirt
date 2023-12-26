/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ada-cruz <ada-cruz@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 19:46:57 by ada-cruz          #+#    #+#             */
/*   Updated: 2022/09/20 00:40:39 by ada-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_substr_len(char const *s, unsigned int start, size_t size)
{
	size_t	s_len;
	size_t	substr_len;

	substr_len = 0;
	s_len = ft_strlen(s);
	if (start >= s_len)
		return (0);
	while (substr_len < size && s[substr_len + start])
		substr_len++;
	return (substr_len);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*substr;
	size_t	substr_len;

	substr_len = ft_substr_len(s, start, len);
	substr = (char *)ft_calloc(substr_len + 1, sizeof(char));
	if (substr == NULL)
		return (NULL);
	i = 0;
	while (i < substr_len && s[start])
	{
		substr[i] = s[start];
		i++;
		start++;
	}
	return (substr);
}
