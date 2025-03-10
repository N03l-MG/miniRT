/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmonzon <nmonzon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 10:27:40 by nmonzon           #+#    #+#             */
/*   Updated: 2024/10/28 11:48:10 by nmonzon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// Concatenate two strings for a specific range
static char	*cat_range(char *dest, char *src, size_t start, size_t end)
{
	size_t	i;

	i = 0;
	while (dest[i] != '\0')
		i++;
	while (start < end && src[start] != '\0')
		dest[i++] = src[start++];
	dest[i] = '\0';
	return (dest);
}

// Use concatenation to return a joint string for a specific range
char	*join_range(char *s1, char *s2, size_t start, size_t end)
{
	size_t	l;
	char	*s_joined;

	if (!s1)
	{
		s1 = (char *)malloc(1);
		if (!s1)
			return (NULL);
		s1[0] = '\0';
	}
	l = ft_strlen(s1) + (end - start);
	s_joined = (char *)malloc(l + 1);
	if (!s_joined)
	{
		free(s1);
		s1 = NULL;
		return (NULL);
	}
	s_joined[0] = '\0';
	cat_range(s_joined, s1, 0, ft_strlen(s1));
	cat_range(s_joined, s2, start, end);
	free(s1);
	s1 = NULL;
	return (s_joined);
}
