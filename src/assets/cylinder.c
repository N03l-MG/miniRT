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

bool	cylinder_intersect(t_cylinder *cyl, t_ray ray, double *t)
{
	t_vector	center;
	t_vector	axis;
	t_vector	oc;
	double		a;
	double		b;
	double		c;
	double		t0;
	double		t1;
	double		y0;
	double		y1;
	double		radius;
	
	center = vec_new(cyl->pos_x, cyl->pos_y, cyl->pos_z);
	axis = vec_normalize(vec_new(cyl->vec_x, cyl->vec_y, cyl->vec_z));
	radius = cyl->diameter / 2.0;
	oc = vec_sub(ray.origin, center);
	t_vector cross1 = vec_cross(ray.direction, axis);
	t_vector cross2 = vec_cross(oc, axis);
	a = vec_dot(cross1, cross1);
	b = 2 * vec_dot(cross1, cross2);
	c = vec_dot(cross2, cross2) - (radius * radius);
	if (!solve_quadratic(a, b, c, &t0, &t1))
		return (false);
	y0 = vec_dot(vec_scale(ray.direction, t0), axis) + vec_dot(oc, axis);
	y1 = vec_dot(vec_scale(ray.direction, t1), axis) + vec_dot(oc, axis);
	if (y0 < 0)
	{
		if (y1 < 0)
			return (false);
		t0 = t1;
		y0 = y1;
	}
	else if (y0 > cyl->height)
	{
		if (y1 > cyl->height)
			return (false);
		t0 = t1;
		y0 = y1;
	}
	*t = t0;
	return (true);
}

t_vector	cylinder_normal(t_cylinder *cyl, t_vector point)
{
    t_vector	center;
	t_vector	axis;
	t_vector	cp;
    
    center = vec_new(cyl->pos_x, cyl->pos_y, cyl->pos_z);
    axis = vec_normalize(vec_new(cyl->vec_x, cyl->vec_y, cyl->vec_z));
    cp = vec_sub(point, center);
    double t = vec_dot(cp, axis);
    t_vector on_axis = vec_add(center, vec_scale(axis, t));
    return vec_normalize(vec_sub(point, on_axis));
}
