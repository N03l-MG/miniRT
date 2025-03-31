/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmonzon <nmonzon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 16:59:54 by nmonzon           #+#    #+#             */
/*   Updated: 2025/03/31 12:43:07 by nmonzon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// Le funny Quake III code (but safer bcs Wextra)
float	fast_inverse_sqrt(float number)
{
	t_float_bits	bits;
	float			x2;

	x2 = number * 0.5F;
	bits.f = number;
	bits.i = 0x5f3759df - (bits.i >> 1);
	bits.f = bits.f * (1.5F - (x2 * bits.f * bits.f));
	return (bits.f);
}

bool	solve_quadratic(float a, float b, float c, t_quad *t)
{
	float	discriminant;

	discriminant = (b * b) - 4 * (a * c);
	if (discriminant < 0)
		return (false);
	t->t0 = (-b - sqrt(discriminant)) / (2.0 * a);
	t->t1 = (-b + sqrt(discriminant)) / (2.0 * a);
	return (true);
}

int	ft_rand(void)
{
	static unsigned int	*seed;

	if (!seed)
	{
		seed = (unsigned int *)gc_malloc(sizeof(unsigned int));
		if (!seed)
			return (0);
		*seed = 42;
	}
	*seed = (1103515245 * *seed + 12345) % (1U << 31);
	return ((int)(*seed & RAND_MAX));
}
