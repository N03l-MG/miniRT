/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgraf <jgraf@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 16:51:50 by nmonzon           #+#    #+#             */
/*   Updated: 2025/03/24 08:54:17 by jgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vector	vec_new(float x, float y, float z)
{
	t_vector	v;

	v.x = x;
	v.y = y;
	v.z = z;
	return (v);
}

t_vector	vec_add(t_vector v1, t_vector v2)
{
	return (vec_new(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z));
}

t_vector	vec_sub(t_vector v1, t_vector v2)
{
	return (vec_new(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z));
}

t_vector	vec_scale(t_vector v, float scale)
{
	return (vec_new(v.x * scale, v.y * scale, v.z * scale));
}

float	vec_dot(t_vector v1, t_vector v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}
