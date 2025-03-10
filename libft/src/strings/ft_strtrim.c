/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmonzon <nmonzon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 12:03:12 by nmonzon           #+#    #+#             */
/*   Updated: 2024/11/25 16:43:32 by nmonzon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// First we find the start and end points of the string, meaning the first point
// at which non of the characters in the set are found both forwards and back.
// Then we create a new string and copy the desired chars into it, effectively
// trimming the set of chars from the start and end.

static size_t	find_start(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;
	int		in_set;

	i = 0;
	while (s1[i] != '\0')
	{
		in_set = 0;
		j = 0;
		while (set[j] != '\0')
		{
			if (set[j] == s1[i])
			{
				in_set = 1;
				break ;
			}
			j++;
		}
		if (!in_set)
			break ;
		i++;
	}
	return (i);
}

static size_t	find_end(char const *s1, char const *set, size_t start)
{
	size_t	i;
	size_t	j;
	int		in_set;

	i = ft_strlen(s1);
	while (i > start)
	{
		in_set = 0;
		j = 0;
		while (set[j] != '\0')
		{
			if (set[j] == s1[i - 1])
			{
				in_set = 1;
				break ;
			}
			j++;
		}
		if (!in_set)
			break ;
		i--;
	}
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trimmed_s;
	size_t	start;
	size_t	end;
	size_t	l;

	start = find_start(s1, set);
	end = find_end(s1, set, start);
	l = end - start;
	trimmed_s = (char *)malloc(l + 1);
	if (!trimmed_s)
		return (NULL);
	ft_strlcpy(trimmed_s, &s1[start], l + 1);
	return (trimmed_s);
}
