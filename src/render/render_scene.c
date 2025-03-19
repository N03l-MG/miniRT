/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmonzon <nmonzon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 17:45:06 by nmonzon           #+#    #+#             */
/*   Updated: 2025/03/19 18:06:10 by nmonzon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static t_vector	get_intersect(t_ray ray, double t)
{
	return vec_add(ray.origin, vec_scale(ray.direction, t));
}

static t_light	*get_scene_light(t_scene_data *data)
{
	t_asset_node	*node;

	node = data->assets->head;
	while (node)
	{
		if (node->type == ASS_LIGHT)
			return ((t_light *)node->asset_struct);
		node = node->next;
	}
	return (NULL);
}

static t_vector	surface_normal(void *obj, t_vector point, t_asset_type type)
{
	if (type == ASS_PLANE)
		return (plane_normal((t_plane *)obj));
	if (type == ASS_SPHERE)
		return (sphere_normal((t_sphere *)obj, point));
	if (type == ASS_CYLINDER)
		return (cylinder_normal((t_cylinder *)obj, point));
	return (vec_new(0, 0, 0));
}

static bool	is_occluded(t_scene_data *data, t_ray shadow_ray, float light_distance)
{
	t_asset_node	*node;
	double			t;

	node = data->assets->head;
	while (node)
	{
		if (node->type == ASS_PLANE)
			if (plane_intersect((t_plane *)node->asset_struct, shadow_ray, &t) 
				&& t > 0.001f && t < light_distance)
				return (true);
		if (node->type == ASS_SPHERE)
			if (sphere_intersect((t_sphere *)node->asset_struct, shadow_ray, &t) 
				&& t > 0.001f && t < light_distance)
				return (true);
		if (node->type == ASS_CYLINDER)
			if (cylinder_intersect((t_cylinder *)node->asset_struct, shadow_ray, &t) 
				&& t > 0.001f && t < light_distance)
				return (true);
		node = node->next;
	}
	return (false);
}

static t_vector	rand_spread(float radius)
{
	t_vector	p;
	do {
		p = vec_new(
			//TODO: make own rand function
			(rand() / (float)RAND_MAX) * 2.0f - 1.0f,
			(rand() / (float)RAND_MAX) * 2.0f - 1.0f,
			(rand() / (float)RAND_MAX) * 2.0f - 1.0f
		);
	} while (vec_length(p) > 1.0f);
	return vec_scale(p, radius);
}

static float	shadow_factor(t_scene_data *data, t_vector intersect, t_vector normal, t_light *light)
{
	t_vector light_pos = vec_new(light->pos_x, light->pos_y, light->pos_z);
	t_vector light_dir = vec_normalize(vec_sub(light_pos, intersect));
	t_ray shadow_ray;
	float light_distance = vec_length(vec_sub(light_pos, intersect));
	shadow_ray.origin = vec_add(intersect, vec_scale(normal, 0.001f));
	shadow_ray.direction = light_dir;

	float shadow_intensity = 0.0f;
	for (int i = 0; i < data->samples; i++)
	{
		t_vector jitter_pos = vec_add(light_pos, rand_spread(1.5f));
		t_vector jitter_dir = vec_normalize(vec_sub(jitter_pos, intersect));
		shadow_ray.direction = jitter_dir;
		if (is_occluded(data, shadow_ray, light_distance))
			shadow_intensity += 1.0f;
	}
	return (1.0f - (shadow_intensity / data->samples));
}

static uint32_t	ray_hit(t_scene_data *data, t_ray ray)
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
	float shadow_intensity = shadow_factor(data, intersect, normal, light);
	float diffuse = fmax(vec_dot(normal, light_dir), 0.0f) * shadow_intensity;
	return (col_rgb(
			fmin((closest_node->col.r * data->ambient->ratio) + (closest_node->col.r * diffuse * light->brightness + data->ambient->col.r * data->ambient->ratio), 0xFF),
			fmin((closest_node->col.g * data->ambient->ratio) + (closest_node->col.g * diffuse * light->brightness + data->ambient->col.g * data->ambient->ratio), 0xFF),
			fmin((closest_node->col.b * data->ambient->ratio) + (closest_node->col.b * diffuse * light->brightness + data->ambient->col.b * data->ambient->ratio), 0xFF),
			0xFF));
}

void	draw_on_image(t_scene_data *data, mlx_image_t *img)
{
	int		i;
	int		j;
	t_ray	ray;

	camera_setup(data->cam);
	i = -1;
	while (++i < WIDTH)
	{
		j = -1;
		while (++j < HEIGHT)
		{
			ray = camera_ray_for_pixel(data->cam, i, j);
			mlx_put_pixel(img, i, j, ray_hit(data, ray));
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
	window_data.mlx_image = mlx_new_image(window_data.mlx_window, WIDTH, HEIGHT);
	if (!window_data.mlx_image)
		fatal_error(ERR_IMAGE, &window_data);
	window_data.image_data = (unsigned char *)window_data.mlx_image->pixels;
	if (!window_data.image_data)
		fatal_error(ERR_DATA, &window_data);
	data->window_data = &window_data;
	draw_on_image(data, window_data.mlx_image);
	mlx_image_to_window(window_data.mlx_window, window_data.mlx_image, 0, 0);
	mlx_key_hook(window_data.mlx_window, &key_hook, data);
	mlx_loop(window_data.mlx_window);
	clean_exit(EXIT_SUCCESS, &window_data);
}
