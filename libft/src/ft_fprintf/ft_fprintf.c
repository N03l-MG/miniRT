/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmonzon <nmonzon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 11:01:32 by nmonzon           #+#    #+#             */
/*   Updated: 2024/10/17 18:02:29 by nmonzon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	write_and_check(int fd, const char c, int *retval)
{
	if (write(fd, &c, 1) == -1)
	{
		*retval = -1;
		return ;
	}
	(*retval)++;
}

static void	handle_format(int fd, const char **str, va_list args, int *retval)
{
	if (**str == 'c')
		handle_character(fd, va_arg(args, int), retval);
	else if (**str == 's')
		handle_string(fd, va_arg(args, char *), retval);
	else if (**str == 'p')
		handle_pointer(fd, va_arg(args, void *), retval);
	else if (**str == 'd' || **str == 'i')
		handle_integer(fd, va_arg(args, int), retval);
	else if (**str == 'u')
		handle_unsigned_decimal(fd, va_arg(args, int), retval);
	else if (**str == 'x')
		handle_hex_lower(fd, va_arg(args, unsigned long), retval);
	else if (**str == 'X')
		handle_hex_upper(fd, va_arg(args, unsigned long), retval);
	else if (**str == '%')
		write_and_check(fd, '%', retval);
	else
		*retval = -2;
}

static int	*format_parse(int fd, const char *str, va_list args, int *retval)
{
	while (*str)
	{
		if (*str == '%' && *++str)
		{
			handle_format(fd, &str, args, retval);
			if (*retval == -1 || *retval == -2)
				return (retval);
		}
		else
		{
			if (write(fd, str, 1) == -1)
			{
				*retval = -1;
				return (retval);
			}
			(*retval)++;
		}
		str++;
	}
	return (retval);
}

int	ft_fprintf(int fd, const char *str, ...)
{
	va_list	args;
	int		retval;

	retval = 0;
	va_start(args, str);
	retval = *format_parse(fd, str, args, &retval);
	va_end(args);
	return (retval);
}
