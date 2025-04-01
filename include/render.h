/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmonzon <nmonzon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 13:42:35 by jgraf             #+#    #+#             */
/*   Updated: 2025/03/31 16:48:03 by nmonzon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "maths.h"
# include "assets.h"
# include "structs.h"

// Argument structs for large functions
typedef struct s_render
{
	t_scene_data	*data;
	t_ray			ray;
	t_asset_node	*closest_node;
	t_asset_type	closest_type;
	double			closest_t;
}	t_render;

typedef struct s_lighting
{
	t_vector		intersect;
	t_vector		normal;
	t_light			*light;
	t_vector		light_dir;
	float			shadow_intensity;
	float			ao;
	float			ambient_light;
	float			diffuse;
	float			specular;
}	t_lighting;

#endif
