/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_char.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmonzon <nmonzon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 12:44:15 by nmonzon           #+#    #+#             */
/*   Updated: 2024/10/17 18:06:57 by nmonzon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	handle_character(int fd, int c, int *retval)
{
	if (write(fd, &c, 1) == -1)
	{
		*retval = -1;
		return ;
	}
	(*retval)++;
}
