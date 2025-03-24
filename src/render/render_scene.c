/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgraf <jgraf@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 17:45:06 by nmonzon           #+#    #+#             */
/*   Updated: 2025/03/24 15:15:11 by jgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static t_asset_node	*find_closest_intersection(t_scene_data *data, t_ray ray,
	double *closest_t, t_asset_type *closest_type)
{
	t_asset_node	*node;
	t_asset_node	*closest_node;
	double			t;

	*closest_t = INFINITY;
	closest_node = NULL;
	*closest_type = NO_TYPE;
	node = data->assets->head;
	while (node)
	{
		if (((node->type == ASS_PLANE
					&& plane_hit((t_plane *)node->asset_struct, ray, &t))
				|| (node->type == ASS_SPHERE
					&& sphere_hit((t_sphere *)node->asset_struct, ray, &t))
				|| (node->type == ASS_CYLINDER
					&& cylinder_hit((t_cylinder *)node->asset_struct, ray, &t)))
			&& (t < *closest_t))
		{
			*closest_t = t;
			closest_node = node;
			*closest_type = node->type;
		}
		node = node->next;
	}
	return (closest_node);
}

static uint32_t	calculate_lighting(t_render *render, int depth)
{
	t_lighting	lighting;
	t_vector	light_pos;
	uint32_t	base_color;

	lighting = init_lighting(render);
	if (!lighting.light)
		return (col_rgb(0, 0, 0, 0xFF));
	light_pos = vec_new(lighting.light->pos_x, lighting.light->pos_y,
			lighting.light->pos_z);
	lighting.light_dir = vec_normalize(vec_sub(light_pos, lighting.intersect));
	lighting.shadow_intensity = shadow_caster(render->data, lighting.intersect,
			lighting.normal, lighting.light);
	lighting.ao = ambient_occlusion(render->data, lighting.intersect,
			lighting.normal);
	lighting.ambient_light = render->data->ambient->ratio * lighting.ao;
	lighting.diffuse = calculate_diffuse(&lighting);
	lighting.specular = calculate_specular(&lighting, render);
	base_color = compute_color(&lighting, render);
	base_color = merge_color(base_color,
			add_reflection(render, lighting, depth),
			render->closest_node->reflect);
	return (base_color);
}

uint32_t	trace_ray(t_scene_data *data, t_ray ray, int depth)
{
	double			closest_t;
	t_asset_node	*closest_node;
	t_asset_type	closest_type;

	closest_node = find_closest_intersection(data, ray,
			&closest_t, &closest_type);
	if (!closest_node)
		return (col_rgb(0, 0, 0, 0xFF));
	return (calculate_lighting(&(t_render){data, ray, closest_node,
			closest_type, closest_t}, depth));
}
