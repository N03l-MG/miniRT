/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgraf <jgraf@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:07:12 by nmonzon           #+#    #+#             */
/*   Updated: 2025/03/24 12:55:16 by jgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static bool	calculate_discriminant(t_sphere *sphere, t_ray ray, t_quad *quad)
{
	t_vector	oc;
	float		b;
	float		discriminant;

	oc = vec_sub(ray.origin, vec_new(sphere->pos_x,
				sphere->pos_y, sphere->pos_z));
	b = 2.0 * vec_dot(oc, ray.direction);
	discriminant = b * b - 4 * vec_dot(ray.direction, ray.direction)
		* (vec_dot(oc, oc) - pow(sphere->diameter / 2.0f, 2));
	if (discriminant < 0)
		return (false);
	quad->t0 = (-b - sqrt(discriminant))
		/ (2.0 * vec_dot(ray.direction, ray.direction));
	quad->t1 = (-b + sqrt(discriminant))
		/ (2.0 * vec_dot(ray.direction, ray.direction));
	return (true);
}

// Main function to check for sphere intersection
bool	sphere_hit(t_sphere *sphere, t_ray ray, double *t)
{
	t_quad		quad;
	float		tmp;

	if (!calculate_discriminant(sphere, ray, &quad))
		return (false);
	if (quad.t0 > quad.t1)
	{
		tmp = quad.t0;
		quad.t0 = quad.t1;
		quad.t1 = tmp;
	}
	if (quad.t0 < 0)
	{
		quad.t0 = quad.t1;
		if (quad.t0 < 0)
			return (false);
	}
	*t = quad.t0;
	return (true);
}

t_vector	sphere_normal(t_sphere *sphere, t_vector point)
{
	t_vector	sphere_center;

	sphere_center = vec_new(sphere->pos_x, sphere->pos_y, sphere->pos_z);
	return (vec_normalize(vec_sub(point, sphere_center)));
}
