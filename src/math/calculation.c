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

// Le funny quake 3 code
float fast_inverse_sqrt(float number)
{
	long	i;
	float	x2;
	float	y;

	x2 = number * 0.5F;
	y = number;
	i = *(long *)&y;
	i = 0x5f3759df - (i >> 1);
	y = *(float *)&i;
	y = y * (1.5F - (x2 * y * y));
	return (y);
}
