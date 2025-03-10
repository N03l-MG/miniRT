/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_int.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmonzon <nmonzon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 12:44:28 by nmonzon           #+#    #+#             */
/*   Updated: 2024/10/17 18:36:26 by nmonzon          ###   ########.fr       */
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

void	handle_integer(int fd, int n, int *retval)
{
	char	*str;

	str = ft_itoa(n);
	if (!str)
	{
		(*retval) = -1;
		return ;
	}
	write_and_check(fd, str, retval, ft_strlen(str));
	free(str);
}
