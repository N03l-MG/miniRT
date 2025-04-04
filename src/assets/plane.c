/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgraf <jgraf@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:07:08 by nmonzon           #+#    #+#             */
/*   Updated: 2025/03/24 12:55:16 by jgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

bool	plane_hit(t_plane *plane, t_ray ray, double *t)
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
		return (false);
	numer = vec_dot(vec_sub(plane_point, ray.origin), plane_normal);
	*t = numer / denom;
	if (*t < 0 || *t > 10000.0)  // Add max render distance of 10,000 units
		return (false);
	return (true);
}

t_vector	plane_normal(t_plane *plane)
{
	return (vec_normalize(vec_new(plane->vec_x, plane->vec_y, plane->vec_z)));
}
