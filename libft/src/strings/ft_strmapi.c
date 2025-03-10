/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmonzon <nmonzon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 12:02:50 by nmonzon           #+#    #+#             */
/*   Updated: 2024/11/25 16:43:32 by nmonzon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Identical to iteri but returns the string after the function is applied to it

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	char	*s_processed;

	i = 0;
	s_processed = (char *)malloc(ft_strlen(s) + 1);
	if (!s_processed)
		return (NULL);
	while (s[i])
	{
		s_processed[i] = f(i, s[i]);
		i++;
	}
	s_processed[i] = '\0';
	return (s_processed);
}
