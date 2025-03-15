/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmonzon <nmonzon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:07:08 by nmonzon           #+#    #+#             */
/*   Updated: 2025/03/13 16:07:09 by nmonzon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

bool	plane_intersect(t_plane *plane, t_ray ray, double *t)
{
	t_vector	plane_normal;
	t_vector	plane_point;
	double		denom;
	double		numer;

	plane_normal = vec_new(plane->vec_x, plane->vec_y, plane->vec_z);
	plane_normal = vec_normalize(plane_normal);
	plane_point = vec_new(plane->pos_x, plane->pos_y, plane->pos_z);
	denom = vec_dot(ray.direction, plane_normal);
	if (fabs(denom) < 1e-6)
		return false;
	numer = vec_dot(vec_sub(plane_point, ray.origin), plane_normal);
	*t = numer / denom;
	return (*t >= 0);
}

t_vector	plane_normal(t_plane *plane)
{
	return vec_normalize(vec_new(plane->vec_x, plane->vec_y, plane->vec_z));
}
