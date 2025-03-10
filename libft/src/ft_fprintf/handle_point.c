/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_point.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmonzon <nmonzon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 12:44:31 by nmonzon           #+#    #+#             */
/*   Updated: 2024/10/17 18:31:08 by nmonzon          ###   ########.fr       */
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

void	handle_pointer(int fd, void *p, int *retval)
{
	uintptr_t	address;
	char		*hex_address;
	int			length;

	write_and_check(fd, "0x", retval, 2);
	if (*retval == -1)
		return ;
	if (!p)
	{
		write_and_check(fd, "0", retval, 1);
		return ;
	}
	address = (uintptr_t)p;
	hex_address = address_to_string(address);
	if (!hex_address)
	{
		(*retval) = -1;
		return ;
	}
	length = ft_strlen(hex_address);
	write_and_check(fd, hex_address, retval, length);
	free(hex_address);
}
