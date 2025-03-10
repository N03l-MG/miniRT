/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmonzon <nmonzon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 12:02:05 by nmonzon           #+#    #+#             */
/*   Updated: 2024/11/25 16:43:32 by nmonzon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Returns the string with its pointer shifted to the first appereace of char c.
// Consider null character as well, use infinte loop. (Insane edgecase honestly)

char	*ft_strchr(const char *s, int c)
{
	int				i;
	unsigned char	un_c;

	i = 0;
	un_c = (unsigned char)c;
	while (1)
	{
		if (s[i] == un_c)
			return ((char *)&s[i]);
		if (s[i] == '\0')
			break ;
		i++;
	}
	if (un_c == '\0')
		return ((char *)&s[i]);
	return (NULL);
}
