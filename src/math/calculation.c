/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmonzon <nmonzon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 16:59:54 by nmonzon           #+#    #+#             */
/*   Updated: 2025/03/14 17:46:00 by nmonzon          ###   ########.fr       */
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
	return bits.f;
}

bool	solve_quadratic(double a, double b, double c, double *t0, double *t1)
{
	double	discriminant;
	double	temp;

	discriminant = (b * b) - 4 * (a * c);
	if (discriminant < 0)
		return (false);
	*t0 = (-b - sqrt(discriminant)) / (2.0 * a);
	*t1 = (-b + sqrt(discriminant)) / (2.0 * a);
	if (*t0 > *t1)
	{
		temp = *t0;
		*t0 = *t1;
		*t1 = temp;
	}
	return (true);
}
