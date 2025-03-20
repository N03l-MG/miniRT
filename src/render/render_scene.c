/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmonzon <nmonzon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 17:45:06 by nmonzon           #+#    #+#             */
/*   Updated: 2025/03/20 16:13:30 by nmonzon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static uint32_t	trace_ray(t_scene_data *data, t_ray ray)
{
	t_asset_node	*node;
	double			t;
	double			closest_t;
	t_asset_node	*closest_node;
	t_asset_type	closest_type;
	t_vector		normal;
	t_vector		intersect;
	t_light			*light;
	t_vector		light_dir;

	closest_t = INFINITY;
	closest_node = NULL;
	node = data->assets->head;
	closest_type = NO_TYPE;
	while (node) //TODO: refactor this hellscape
	{
		if (node->type == ASS_PLANE)
		{
			if (plane_intersect((t_plane *)node->asset_struct, ray, &t)
				&& t < closest_t)
			{
				closest_t = t;
				closest_node = node;
				closest_type = node->type;
			}
		}
		if (node->type == ASS_SPHERE)
		{
			if (sphere_intersect((t_sphere *)node->asset_struct, ray, &t)
				&& t < closest_t)
			{
				closest_t = t;
				closest_node = node;
				closest_type = node->type;
			}
		}
		if (node->type == ASS_CYLINDER)
		{
			if (cylinder_intersect((t_cylinder *)node->asset_struct, ray, &t)
				&& t < closest_t)
			{
				closest_t = t;
				closest_node = node;
				closest_type = node->type;
			}
		}
		node = node->next;
	}
	if (!closest_node)
		return (col_rgb(0, 0, 0, 0xFF));
	intersect = get_intersect(ray, closest_t);
	normal = surface_normal(closest_node->asset_struct, intersect, closest_type);
	light = get_scene_light(data);
	if (!light)
		return (col_rgb(0, 0, 0, 0xFF));
	t_vector light_pos = vec_new(light->pos_x, light->pos_y, light->pos_z);
	light_dir = vec_normalize(vec_sub(light_pos, intersect));
	float shadow_intensity = shadow_caster(data, intersect, normal, light);
	float ao = ambient_occlusion(data, intersect, normal);
    float ambient_light = data->ambient->ratio * ao;
    float diffuse = fmax(vec_dot(normal, light_dir), 0.0f) * shadow_intensity;
    
    return (col_rgb(
        fmin((closest_node->col.r * ambient_light) + 
             (closest_node->col.r * diffuse * light->brightness * (light->col.r / 255.0f) + 
              data->ambient->col.r * ambient_light), 0xFF),
        fmin((closest_node->col.g * ambient_light) + 
             (closest_node->col.g * diffuse * light->brightness * (light->col.g / 255.0f) + 
              data->ambient->col.g * ambient_light), 0xFF),
        fmin((closest_node->col.b * ambient_light) + 
             (closest_node->col.b * diffuse * light->brightness * (light->col.b / 255.0f) + 
              data->ambient->col.b * ambient_light), 0xFF),
        0xFF));
}

void	draw_frame(t_scene_data *data, mlx_image_t *img)
{
	int		i;
	int		j;
	t_ray	ray;

	camera_setup(data->cam);
	i = -1;
	while (++i < HEIGHT)
	{
		j = -1;
		while (++j < WIDTH)
		{
			ray = camera_ray_for_pixel(data->cam, j, i);
			mlx_put_pixel(img, j, i, trace_ray(data, ray));
		}
	}
}

void	render_scene(t_scene_data *data)
{
	t_window_data	window_data;

	window_data.mlx_window = mlx_init(WIDTH, HEIGHT, "miniRT", false);
	if (!window_data.mlx_window)
		fatal_error(ERR_WINDOW, &window_data);
	window_data.mlx_image = mlx_new_image(window_data.mlx_window, WIDTH, HEIGHT);
	if (!window_data.mlx_image)
		fatal_error(ERR_IMAGE, &window_data);
	window_data.image_data = (unsigned char *)window_data.mlx_image->pixels;
	if (!window_data.image_data)
		fatal_error(ERR_DATA, &window_data);
	data->window_data = &window_data;
	draw_frame(data, window_data.mlx_image);
	mlx_image_to_window(window_data.mlx_window, window_data.mlx_image, 0, 0);
	mlx_key_hook(window_data.mlx_window, &key_hook, data);
	mlx_loop(window_data.mlx_window);
	clean_exit(EXIT_SUCCESS, &window_data);
}
