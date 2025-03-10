/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmonzon <nmonzon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 12:44:21 by nmonzon           #+#    #+#             */
/*   Updated: 2024/10/17 18:37:34 by nmonzon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	write_and_check(int fd, char *s, int *retval, int length)
{
	if (write(fd, s, length) == -1)
	{
		*retval = -1;
		return ;
	}
	*retval += length;
}

static char	*itoa_unsigned(unsigned int n)
{
	char			*s;
	int				l;
	unsigned int	tmp;

	tmp = n;
	l = 0;
	if (n == 0)
		return (ft_strdup("0"));
	while (tmp > 0)
	{
		tmp /= 10;
		l++;
	}
	s = (char *)malloc(l + 1);
	if (!s)
		return (NULL);
	s[l] = '\0';
	while (l--)
	{
		s[l] = (n % 10) + '0';
		n /= 10;
	}
	return (s);
}

void	handle_unsigned_decimal(int fd, int ud, int *retval)
{
	char			*str;
	unsigned int	un_d;

	un_d = (unsigned int)ud;
	str = itoa_unsigned(un_d);
	if (!str)
	{
		(*retval) = -1;
		return ;
	}
	write_and_check(fd, str, retval, ft_strlen(str));
	free(str);
}
