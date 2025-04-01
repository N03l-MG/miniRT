/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadows.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmonzon <nmonzon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 10:56:02 by jgraf             #+#    #+#             */
/*   Updated: 2025/03/31 12:44:46 by nmonzon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static t_vector	rand_spread(float radius)
{
	t_vector	p;

	p = vec_new(
			(ft_rand() / (float)RAND_MAX) * 2.0f - 1.0f,
			(ft_rand() / (float)RAND_MAX) * 2.0f - 1.0f,
			(ft_rand() / (float)RAND_MAX) * 2.0f - 1.0f
			);
	while (vec_length(p) > 1.0f)
	{
		p = vec_new(
				(ft_rand() / (float)RAND_MAX) * 2.0f - 1.0f,
				(ft_rand() / (float)RAND_MAX) * 2.0f - 1.0f,
				(ft_rand() / (float)RAND_MAX) * 2.0f - 1.0f
				);
	}
	return (vec_scale(p, radius));
}

static float	calculate_shadow_intensity(t_scene_data *data,
	t_vector intersect, t_vector light_pos, t_ray shadow_ray)
{
	t_vector	jitter_pos;
	t_vector	jitter_dir;
	float		light_distance;
	float		shadow_intensity;
	int			i;

	i = 0;
	shadow_intensity = 0;
	light_distance = vec_length(vec_sub(light_pos, intersect));
	while (i < data->samples)
	{
		jitter_pos = vec_add(light_pos, rand_spread(1.5f));
		jitter_dir = vec_normalize(vec_sub(jitter_pos, intersect));
		shadow_ray.direction = jitter_dir;
		if (is_occluded(data, shadow_ray, light_distance))
			shadow_intensity += 1.0f
				- (fmax(fmin(light_distance, 500.0f), 0.0f) / 500);
		i++;
	}
	return (shadow_intensity);
}

float	shadow_caster(t_scene_data *data, t_vector intersect, t_vector normal,
	t_light *light)
{
	t_vector	light_pos;
	t_vector	light_dir;
	t_ray		shadow_ray;

	light_pos = vec_new(light->pos_x, light->pos_y, light->pos_z);
	light_dir = vec_normalize(vec_sub(light_pos, intersect));
	shadow_ray.origin = vec_add(intersect, vec_scale(normal, 0.001f));
	shadow_ray.direction = light_dir;
	if (vec_dot(normal, light_dir) < 0)
		return (0);
	return (1.0f - (calculate_shadow_intensity(data, intersect,
				light_pos, shadow_ray) / data->samples));
}

static float	check_ao_intersections(t_scene_data *data, t_ray ao_ray,
			float max_distance)
{
	t_asset_node	*node;
	float			occlusion;
	double			t;

	node = data->assets->head;
	occlusion = 0;
	while (node)
	{
		if (node->type == AST_PLANE)
		{
			if (plane_hit((t_plane *)node->asset_struct, ao_ray, &t)
				&& t > 0.001f && t < max_distance)
				occlusion += 1.0f;
		}
		node = node->next;
	}
	return (occlusion);
}

float	ambient_occlusion(t_scene_data *data, t_vector point, t_vector normal)
{
	float		occlusion;
	float		max_distance;
	int			i;
	t_vector	random_dir;
	t_ray		ao_ray;

	occlusion = 0;
	max_distance = 2;
	i = 0;
	while (i < data->samples)
	{
		random_dir = rand_spread(1.0f);
		if (vec_dot(random_dir, normal) < 0)
			random_dir = vec_scale(random_dir, -1.0f);
		ao_ray.origin = vec_add(point, vec_scale(normal, 0.001f));
		ao_ray.direction = vec_normalize(random_dir);
		occlusion += check_ao_intersections(data, ao_ray, max_distance);
		i++;
	}
	return (1.0f - (occlusion / (float)data->samples));
}
