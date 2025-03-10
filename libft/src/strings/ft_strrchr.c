/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmonzon <nmonzon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 12:03:08 by nmonzon           #+#    #+#             */
/*   Updated: 2024/11/25 16:43:32 by nmonzon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Reversed version of strchr. Uses strlen to find the end and read backwards.

char	*ft_strrchr(const char *s, int c)
{
	int				i;
	unsigned char	un_c;

	i = ft_strlen(s);
	un_c = (unsigned char)c;
	while (i >= 0)
	{
		if (s[i] == un_c)
			return ((char *)&s[i]);
		i--;
	}
	if (un_c == '\0')
		return ((char *)&s[ft_strlen(s)]);
	return (NULL);
}
