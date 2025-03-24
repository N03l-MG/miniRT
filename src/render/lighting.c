/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgraf <jgraf@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 13:51:15 by jgraf             #+#    #+#             */
/*   Updated: 2025/03/24 14:00:41 by jgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_lighting	init_lighting(t_render *render)
{
	t_lighting	lighting;

	lighting.intersect = get_intersect(render->ray, render->closest_t);
	lighting.normal = surface_normal(render->closest_node->asset_struct,
			lighting.intersect, render->closest_type);
	lighting.light = get_scene_light(render->data);
	return (lighting);
}

float	calculate_diffuse(t_lighting *lighting)
{
	return (fmax(vec_dot(lighting->normal, lighting->light_dir),
			0.0f) * lighting->shadow_intensity);
}

float	calculate_specular(t_lighting *lighting, t_render *render)
{
	t_vector	view_dir;
	t_vector	reflect_dir;

	view_dir = vec_normalize(vec_sub(render->ray.origin,
				lighting->intersect));
	reflect_dir = vec_sub(vec_scale(lighting->light_dir, -1),
			vec_scale(lighting->normal, 2
				* vec_dot(vec_scale(lighting->light_dir, -1),
					lighting->normal)));
	return (pow(fmax(vec_dot(view_dir, reflect_dir), 0.0f), 32)
		* lighting->shadow_intensity * render->closest_node->roughness);
}

uint32_t	compute_color(t_lighting *lighting, t_render *render)
{
	t_color	col;

	col.r = fmin((render->closest_node->col.r * lighting->ambient_light)
			+ (render->closest_node->col.r * lighting->diffuse
				* lighting->light->brightness
				* (lighting->light->col.r / 255.0f))
			+ (lighting->light->col.r * lighting->specular
				* lighting->light->brightness
				* lighting->shadow_intensity), 0xFF);
	col.g = fmin((render->closest_node->col.g * lighting->ambient_light)
			+ (render->closest_node->col.g * lighting->diffuse
				* lighting->light->brightness
				* (lighting->light->col.g / 255.0f))
			+ (lighting->light->col.g * lighting->specular
				* lighting->light->brightness
				* lighting->shadow_intensity), 0xFF);
	col.b = fmin((render->closest_node->col.b * lighting->ambient_light)
			+ (render->closest_node->col.b * lighting->diffuse
				* lighting->light->brightness
				* (lighting->light->col.b / 255.0f))
			+ (lighting->light->col.b * lighting->specular
				* lighting->light->brightness
				* lighting->shadow_intensity), 0xFF);
	return (col_rgb(col.r, col.g, col.b, 0xFF));
}
