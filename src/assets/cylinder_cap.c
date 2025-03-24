/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_cap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgraf <jgraf@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 10:24:36 by jgraf             #+#    #+#             */
/*   Updated: 2025/03/24 10:26:05 by jgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static bool	intersect_bottom_cap(t_cylinder *cyl, t_ray ray, double *t)
{
	t_vector	center;
	t_vector	axis;
	t_vector	hit;
	double		cap;

	center = vec_new(cyl->pos_x, cyl->pos_y, cyl->pos_z);
	axis = vec_normalize(vec_new(cyl->vec_x, cyl->vec_y, cyl->vec_z));
	cap = vec_dot(vec_sub(center, ray.origin), axis)
		/ vec_dot(ray.direction, axis);
	if (cap > 0)
	{
		hit = vec_add(ray.origin, vec_scale(ray.direction, cap));
		if (vec_length(vec_sub(hit, center)) <= cyl->diameter / 2.0)
		{
			*t = cap;
			return (true);
		}
	}
	return (false);
}

static bool	intersect_top_cap(t_cylinder *cyl, t_ray ray, double *t, bool found)
{
	t_vector	center;
	t_vector	axis;
	t_vector	hit;
	t_vector	top_center;
	double		cap;

	center = vec_new(cyl->pos_x, cyl->pos_y, cyl->pos_z);
	axis = vec_normalize(vec_new(cyl->vec_x, cyl->vec_y, cyl->vec_z));
	top_center = vec_add(center, vec_scale(axis, cyl->height));
	cap = vec_dot(vec_sub(top_center, ray.origin), axis)
		/ vec_dot(ray.direction, axis);
	if (cap > 0 && (!found || cap < *t))
	{
		hit = vec_add(ray.origin, vec_scale(ray.direction, cap));
		if (vec_length(vec_sub(hit, top_center)) <= cyl->diameter / 2.0)
		{
			*t = cap;
			return (true);
		}
	}
	return (false);
}

bool	intersect_caps(t_cylinder *cyl, t_ray ray, double *t)
{
	bool	hit_found;

	hit_found = intersect_bottom_cap(cyl, ray, t);
	hit_found |= intersect_top_cap(cyl, ray, t, hit_found);
	return (hit_found);
}
