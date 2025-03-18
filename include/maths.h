/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmonzon <nmonzon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 16:50:58 by nmonzon           #+#    #+#             */
/*   Updated: 2025/03/14 17:43:11 by nmonzon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATHS_H
# define MATHS_H

typedef union u_float_bits
{
    float	f;
    int32_t	i;
}	t_float_bits;

typedef struct s_vector
{
    float x;
    float y;
    float z;
}   t_vector;

typedef struct s_ray
{
    t_vector origin;
    t_vector direction;
}   t_ray;

typedef struct s_tuple
{
    float x;
    float y;
    float z;
    float w;  // w=1 for point, w=0 for vector
}   t_tuple;

// Vector operations
t_vector    vec_new(float x, float y, float z);
t_vector    vec_add(t_vector v1, t_vector v2);
t_vector    vec_sub(t_vector v1, t_vector v2);
t_vector    vec_scale(t_vector v, float scale);
float       vec_dot(t_vector v1, t_vector v2);
t_vector    vec_cross(t_vector v1, t_vector v2);
float		vec_length(t_vector v);
t_vector    vec_normalize(t_vector v);
t_vector	vec_random(float min, float max);

// // Ray operations
// t_ray       ray_new(t_vector origin, t_vector direction);
// t_vector    ray_at(t_ray ray, float t);

// Math calculations
float		fast_inverse_sqrt(float number);
bool		solve_quadratic(float a, float b, float c, float *t0, float *t1);


#endif
