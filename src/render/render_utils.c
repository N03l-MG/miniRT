/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kixik   <github.com/kixikCodes>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 10:55:15 by jgraf             #+#    #+#             */
/*   Updated: 2025/03/31 13:05:19 by kixik            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vector	get_intersect(t_ray ray, double t)
{
	return (vec_add(ray.origin, vec_scale(ray.direction, t)));
}

t_light	*get_scene_light(t_scene_data *data)
{
	t_asset_node	*node;

	node = data->assets->head;
	while (node)
	{
		if (node->type == AST_LIGHT)
			return ((t_light *)node->asset_struct);
		node = node->next;
	}
	return (NULL);
}

t_vector surface_normal(void *obj, t_vector point, t_asset_type type)
{
    if (type == AST_PLANE)
        return plane_normal((t_plane *)obj);
    else if (type == AST_SPHERE)
        return sphere_normal((t_sphere *)obj, point);
    else if (type == AST_CYLINDER)
        return cylinder_normal((t_cylinder *)obj, point);
    else if (type == AST_OBJ)
        return obj_normal((t_obj *)obj, ((t_obj *)obj)->hit_face);
    return (t_vector){0, 0, 0};
}

bool	is_occluded(t_scene_data *data, t_ray shadow_ray, float light_distance)
{
	t_asset_node	*node;
	double			t;

	node = data->assets->head;
	while (node)
	{
		if (node->type == AST_PLANE
			&& (plane_hit((t_plane *)node->asset_struct, shadow_ray, &t)
				&& t > 0.001f && t < light_distance))
			return (true);
		else if (node->type == AST_SPHERE
			&& (sphere_hit((t_sphere *)node->asset_struct, shadow_ray, &t)
				&& t > 0.001f && t < light_distance))
			return (true);
		else if (node->type == AST_CYLINDER
			&& (cylinder_hit((t_cylinder *)node->asset_struct, shadow_ray, &t)
				&& t > 0.001f && t < light_distance))
			return (true);
		else if (node->type == AST_OBJ
			&& (obj_hit((t_obj *)node->asset_struct, shadow_ray, &t)
				&& t > 0.001f && t < light_distance))
			return (true);
		node = node->next;
	}
	return (false);
}
