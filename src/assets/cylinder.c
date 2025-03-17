/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmonzon <nmonzon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:07:15 by nmonzon           #+#    #+#             */
/*   Updated: 2025/03/13 16:07:15 by nmonzon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static bool intersect_caps(t_cylinder *cyl, t_ray ray, double *t)
{
	t_vector	center;
	t_vector	axis;
	double		radius;
	double		denom;
	t_vector	hit;
	double		t_cap;
	t_vector	top_center;

	center = vec_new(cyl->pos_x, cyl->pos_y, cyl->pos_z);
	axis = vec_normalize(vec_new(cyl->vec_x, cyl->vec_y, cyl->vec_z));
	radius = cyl->diameter / 2.0;
	denom = vec_dot(ray.direction, axis);
	if (fabs(denom) > 1e-6)
	{
		t_cap = vec_dot(vec_sub(center, ray.origin), axis) / denom;
		hit = vec_add(ray.origin, vec_scale(ray.direction, t_cap));
		if (t_cap > 0 && vec_length(vec_sub(hit, center)) <= radius)
		{
			*t = t_cap;
			return (true);
		}
	}
	top_center = vec_add(center, vec_scale(axis, cyl->height));
	denom = vec_dot(ray.direction, axis);
	if (fabs(denom) > 1e-6)
	{
		double t_cap = vec_dot(vec_sub(top_center, ray.origin), axis) / denom;
		hit = vec_add(ray.origin, vec_scale(ray.direction, t_cap));
		if (t_cap > 0 && vec_length(vec_sub(hit, top_center)) <= radius)
		{
			*t = t_cap;
			return (true);
		}
	}
	return (false);
}

bool cylinder_intersect(t_cylinder *cyl, t_ray ray, double *t)
{
	t_vector    center;
	t_vector    axis;
	t_vector    oc;
	float       a;
	float       b;
	float       c;
	float       t0;
	float       t1;
	float       radius;
	
	center = vec_new(cyl->pos_x, cyl->pos_y, cyl->pos_z);
	axis = vec_normalize(vec_new(cyl->vec_x, cyl->vec_y, cyl->vec_z));
	radius = cyl->diameter / 2.0;
	oc = vec_sub(ray.origin, center);
	a = vec_dot(vec_cross(ray.direction, axis), vec_cross(ray.direction, axis));
	b = 2 * vec_dot(vec_cross(ray.direction, axis), vec_cross(oc, axis));
	c = vec_dot(vec_cross(oc, axis), vec_cross(oc, axis)) - (radius * radius);
	if (!solve_quadratic(a, b, c, &t0, &t1))
		return (intersect_caps(cyl, ray, t));
	float h0 = vec_dot(vec_sub(vec_add(ray.origin, vec_scale(ray.direction, t0)),
		center), axis);
	float h1 = vec_dot(vec_sub(vec_add(ray.origin, vec_scale(ray.direction, t1)),
		center), axis);
	if (!(h0 >= 0 && h0 <= cyl->height) && !(h1 >= 0 && h1 <= cyl->height))
		return (intersect_caps(cyl, ray, t));
	if (!(h0 >= 0 && h0 <= cyl->height))
		t0 = t1;
	else if (!(h1 >= 0 && h1 <= cyl->height))
		t1 = t0;
	*t = (t0 < t1) ? t0 : t1;
	double t_caps;
	if (intersect_caps(cyl, ray, &t_caps) && t_caps < *t)
		*t = t_caps;
	return (*t > 0);
}

t_vector	cylinder_normal(t_cylinder *cyl, t_vector point)
{
	t_vector	center;
	t_vector	axis;
	t_vector	cp;

	center = vec_new(cyl->pos_x, cyl->pos_y, cyl->pos_z);
	axis = vec_normalize(vec_new(cyl->vec_x, cyl->vec_y, cyl->vec_z));
	cp = vec_sub(point, center);
	if (fabs(vec_dot(cp, axis)) < 0.001f)
		return (vec_scale(axis, -1.0));
	if (fabs(vec_dot(vec_sub(point, 
		vec_add(center, vec_scale(axis, cyl->height))), axis)) < 0.001f)
		return (axis);
	return (vec_normalize(vec_sub(point, vec_add(center,
		vec_scale(axis, vec_dot(cp, axis))))));
}
