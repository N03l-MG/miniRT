/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgraf <jgraf@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:07:15 by nmonzon           #+#    #+#             */
/*   Updated: 2025/03/24 12:54:29 by jgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static bool	cylinder_body(t_cylinder *cyl, t_ray ray, t_quad *quad, double *t)
{
	t_vector	center;
	t_vector	axis;
	double		h0;
	double		h1;

	center = vec_new(cyl->pos_x, cyl->pos_y, cyl->pos_z);
	axis = vec_normalize(vec_new(cyl->vec_x, cyl->vec_y, cyl->vec_z));
	h0 = vec_dot(vec_sub(vec_add(ray.origin,
					vec_scale(ray.direction, quad->t0)), center), axis);
	h1 = vec_dot(vec_sub(vec_add(ray.origin,
					vec_scale(ray.direction, quad->t1)), center), axis);
	if ((h0 < 0 || h0 > cyl->height) && (h1 < 0 || h1 > cyl->height))
		return (false);
	if (h0 < 0 || h0 > cyl->height)
		quad->t0 = quad->t1;
	else if (h1 < 0 || h1 > cyl->height)
		quad->t1 = quad->t0;
	*t = quad->t1;
	if (quad->t0 < quad->t1)
		*t = quad->t0;
	return (true);
}

bool	cylinder_hit(t_cylinder *cyl, t_ray ray, double *t)
{
	t_vector	center;
	t_vector	axis;
	t_quad		quad;
	float		radius;
	double		caps;

	center = vec_new(cyl->pos_x, cyl->pos_y, cyl->pos_z);
	axis = vec_normalize(vec_new(cyl->vec_x, cyl->vec_y, cyl->vec_z));
	radius = cyl->diameter / 2;
	quad.a = vec_dot(vec_cross(ray.direction, axis),
			vec_cross(ray.direction, axis));
	quad.b = vec_dot(vec_cross(ray.direction, axis),
			vec_cross(vec_sub(ray.origin, center), axis)) * 2;
	quad.c = vec_dot(vec_cross(vec_sub(ray.origin, center), axis),
			vec_cross(vec_sub(ray.origin, center), axis)) - (radius * radius);
	if (!solve_quadratic(quad.a, quad.b, quad.c, &quad))
		return (intersect_caps(cyl, ray, t));
	if (!cylinder_body(cyl, ray, &quad, t))
		return (intersect_caps(cyl, ray, t));
	if (intersect_caps(cyl, ray, &caps) && caps < *t)
		*t = caps;
	return (*t > 0);
}

t_vector	cylinder_normal(t_cylinder *cyl, t_vector point)
{
	t_vector	center;
	t_vector	axis;
	float		dist_to_bottom;

	center = vec_new(cyl->pos_x, cyl->pos_y, cyl->pos_z);
	axis = vec_normalize(vec_new(cyl->vec_x, cyl->vec_y, cyl->vec_z));
	dist_to_bottom = fabs(vec_dot(vec_sub(point, center), axis));
	if (dist_to_bottom < 0.001f)
		return (vec_scale(axis, -1.0f));
	if (fabs(vec_dot(vec_sub(point, vec_add(center,
						vec_scale(axis, cyl->height))), axis)) < 0.001f)
		return (axis);
	return (vec_normalize(vec_sub(vec_sub(point, center),
				vec_scale(axis, vec_dot(vec_sub(point, center), axis)))));
}
