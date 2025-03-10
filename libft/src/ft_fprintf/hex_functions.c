/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hex_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmonzon <nmonzon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 11:24:32 by nmonzon           #+#    #+#             */
/*   Updated: 2024/10/17 16:13:13 by nmonzon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	hex_length(unsigned long address)
{
	int	l;

	l = 0;
	if (address == 0)
		return (1);
	while (address > 0)
	{
		address /= 16;
		l++;
	}
	return (l);
}

char	*hex_to_string(unsigned int hex)
{
	int		length;
	int		i;
	char	*output;
	char	*hex_digits;

	hex_digits = "0123456789abcdef";
	length = hex_length(hex);
	output = (char *)malloc(length + 1);
	if (!output)
		return (NULL);
	output[length] = '\0';
	i = length;
	while (i > 0)
	{
		output[--i] = hex_digits[hex % 16];
		hex /= 16;
	}
	return (output);
}

char	*address_to_string(uintptr_t address)
{
	int		length;
	int		i;
	char	*output;
	char	*hex_digits;

	hex_digits = "0123456789abcdef";
	length = hex_length(address);
	output = (char *)malloc(length + 1);
	if (!output)
		return (NULL);
	output[length] = '\0';
	i = length;
	while (i > 0)
	{
		output[--i] = hex_digits[address % 16];
		address /= 16;
	}
	return (output);
}

// FYI, this could be done more efficiently with bitshift and masking:
	// i = hex_length(address);
	// while (i > 0)
	// {
	// 	current_digit = hex_digits[(address >> (i * 4)) & 0xF];
	// 	write(1, &current_digit, 1);
	// 	i--;
	// }
// But I chose not to use this as it is very complicated to explain.
