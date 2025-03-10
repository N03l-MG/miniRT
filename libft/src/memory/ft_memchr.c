/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmonzon <nmonzon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 12:00:54 by nmonzon           #+#    #+#             */
/*   Updated: 2024/11/25 16:43:32 by nmonzon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Locates and returns the adress of the character c in string s.
// Casts to unsigned char account for weird number edge cases.

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	us_c;
	unsigned char	*us_s;

	i = 0;
	us_c = (unsigned char)c;
	us_s = (unsigned char *)s;
	while (i < n)
	{
		if (us_s[i] == us_c)
			return ((void *)&us_s[i]);
		i++;
	}
	return (NULL);
}
