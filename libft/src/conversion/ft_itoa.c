/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmonzon <nmonzon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 12:00:09 by nmonzon           #+#    #+#             */
/*   Updated: 2024/11/25 16:43:32 by nmonzon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Uses modulo and divsion by 10 to convert integers to strings.
// Accounts for minint and counts the digits to malloc the string.

// helper function for malloc
static int	count_digits(int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		i++;
		n = -n;
	}
	while (n > 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static char	*handle_min(void)
{
	char	*s;

	s = (char *)malloc(12);
	if (!s)
		return (NULL);
	ft_strlcpy(s, "-2147483648", 12);
	return (s);
}

char	*ft_itoa(int n)
{
	char	*s;
	int		l;
	int		neg;

	if (n == INT_MIN)
		return (handle_min());
	neg = (n < 0);
	l = count_digits(n);
	s = (char *)malloc(l + 1);
	if (!s)
		return (NULL);
	s[l] = '\0';
	if (neg)
		n = -n;
	while (l--)
	{
		s[l] = (n % 10) + '0';
		n /= 10;
	}
	if (neg)
		s[0] = '-';
	return (s);
}
