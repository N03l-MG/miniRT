/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgraf <jgraf@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 17:16:05 by nmonzon           #+#    #+#             */
/*   Updated: 2025/03/24 11:42:12 by jgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static t_vector	calculate_pixel_position(t_camera *cam, float px, float py)
{
	float		fov_adjustment;
	float		x_offset;
	float		y_offset;
	t_vector	direction;
	t_vector	right;

	fov_adjustment = tan(cam->fov * M_PI / 360.0);
	x_offset = (2 * ((px + 0.5) / WIDTH) - 1) * ((float)WIDTH / (float)HEIGHT)
		* fov_adjustment;
	y_offset = (1 - 2 * ((py + 0.5) / HEIGHT)) * fov_adjustment;
	direction = vec_normalize(vec_new(cam->vec_x, cam->vec_y, cam->vec_z));
	right = vec_normalize(vec_cross(direction, vec_new(0, 1, 0)));
	return (vec_normalize(vec_add(direction, vec_add(vec_scale(right, x_offset),
					vec_scale(vec_cross(right, direction), y_offset)))));
}

void	camera_setup(t_camera *cam)
{
	t_vector	direction;

	direction = vec_normalize(vec_new(cam->vec_x, cam->vec_y, cam->vec_z));
	cam->vec_x = direction.x;
	cam->vec_y = direction.y;
	cam->vec_z = direction.z;
}

t_ray	camera_ray_for_pixel(t_camera *cam, float px, float py)
{
	t_ray	ray;

	ray.origin = vec_new(cam->pos_x, cam->pos_y, cam->pos_z);
	ray.direction = calculate_pixel_position(cam, px, py);
	return (ray);
}
