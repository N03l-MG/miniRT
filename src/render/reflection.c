/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgraf <jgraf@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 15:07:44 by jgraf             #+#    #+#             */
/*   Updated: 2025/03/24 15:17:19 by jgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

uint32_t	add_reflection(t_render *render, t_lighting lighting, int depth)
{
	uint32_t	reflected_color;
	t_ray		reflected_ray;
	t_vector	reflect_dir;

	if (depth < MAX_REFLECT && render->closest_node->reflect > 0.0f)
	{
		reflect_dir = vec_sub(render->ray.direction,
				vec_scale(lighting.normal, 2 * vec_dot(render->ray.direction,
						lighting.normal)));
		reflected_ray.origin = vec_add(lighting.intersect,
				vec_scale(reflect_dir, 0.001f));
		reflected_ray.direction = vec_normalize(reflect_dir);
		reflected_color = trace_ray(render->data, reflected_ray, depth + 1);
		return (reflected_color);
	}
	return (0);
}
