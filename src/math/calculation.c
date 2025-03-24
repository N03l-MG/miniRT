/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgraf <jgraf@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 16:59:54 by nmonzon           #+#    #+#             */
/*   Updated: 2025/03/24 09:02:51 by jgraf            ###   ########.fr       */
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
