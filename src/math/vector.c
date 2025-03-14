/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmonzon <nmonzon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 16:51:50 by nmonzon           #+#    #+#             */
/*   Updated: 2025/03/14 17:24:19 by nmonzon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vector    vec_new(float x, float y, float z)
{
    t_vector v;

    v.x = x;
    v.y = y;
    v.z = z;
    return (v);
}

t_vector    vec_add(t_vector v1, t_vector v2)
{
    return (vec_new(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z));
}

t_vector    vec_sub(t_vector v1, t_vector v2)
{
    return (vec_new(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z));
}

t_vector    vec_scale(t_vector v, float scale)
{
    return (vec_new(v.x * scale, v.y * scale, v.z * scale));
}

float       vec_dot(t_vector v1, t_vector v2)
{
    return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

t_vector    vec_cross(t_vector v1, t_vector v2)
{
    return (vec_new(
        v1.y * v2.z - v1.z * v2.y,
        v1.z * v2.x - v1.x * v2.z,
        v1.x * v2.y - v1.y * v2.x
    ));
}

float       vec_length(t_vector v)
{
    return (sqrt(vec_dot(v, v)));
}

t_vector    vec_normalize(t_vector v)
{
    float length;

    length = vec_length(v);
    if (length == 0)
        return (vec_new(0, 0, 0));
    return (vec_scale(v, 1.0f / length));
}
