/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgraf <jgraf@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 08:51:48 by jgraf             #+#    #+#             */
/*   Updated: 2025/03/24 08:54:00 by jgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

float	vec_length(t_vector v)
{
	return (sqrt(vec_dot(v, v)));
}

t_vector	vec_cross(t_vector v1, t_vector v2)
{
	return (vec_new(
			v1.y * v2.z - v1.z * v2.y,
			v1.z * v2.x - v1.x * v2.z,
			v1.x * v2.y - v1.y * v2.x
		));
}

t_vector	vec_normalize(t_vector v)
{
	float	length_squared;

	length_squared = vec_dot(v, v);
	if (length_squared == 0)
		return (vec_new(0, 0, 0));
	return (vec_scale(v, fast_inverse_sqrt(length_squared)));
}

static float	rand_range(float min, float max)
{
	return (min + (max - min) * ((float)ft_rand() / RAND_MAX));
}

t_vector	vec_random(float min, float max)
{
	return ((t_vector){
		.x = rand_range(min, max),
		.y = rand_range(min, max),
		.z = rand_range(min, max)
	});
}
