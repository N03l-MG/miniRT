/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmonzon <nmonzon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 17:45:06 by nmonzon           #+#    #+#             */
/*   Updated: 2025/03/14 17:22:28 by nmonzon          ###   ########.fr       */
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

static bool	is_occluded(t_scene_data *data, t_ray shadow_ray)
{
	t_asset_node	*node;
	double			t;

	node = data->assets->head;
	while (node)
	{
		if (node->type == ASS_PLANE)
			if (plane_intersect((t_plane *)node->asset_struct, shadow_ray, &t) && t > 0.001f)
				return (true);
		if (node->type == ASS_SPHERE)
			if (sphere_intersect((t_sphere *)node->asset_struct, shadow_ray, &t) && t > 0.001f)
				return (true);
		if (node->type == ASS_CYLINDER)
			if (cylinder_intersect((t_cylinder *)node->asset_struct, shadow_ray, &t) && t > 0.001f)
				return (true);
		node = node->next;
	}
	return (false);
}

static uint32_t	ray_hit(t_scene_data *data, t_ray ray)
{
	t_asset_node	*node;
	double			t;
	double			closest_t;
	void			*closest_obj;
	t_asset_type	closest_type;
	t_vector		normal;
	t_vector		intersect;
	t_light			*light;
	t_vector		light_dir;
	t_ray			shadow_ray;

	closest_t = INFINITY;
	closest_obj = NULL;
	node = data->assets->head;
	closest_type = NO_TYPE;
	while (node)
	{
		if (node->type == ASS_PLANE)
		{
			if (plane_intersect((t_plane *)node->asset_struct, ray, &t)
				&& t < closest_t)
			{
				closest_t = t;
				closest_obj = node->asset_struct;
				closest_type = node->type;
			}
		}
		if (node->type == ASS_SPHERE)
		{
			if (sphere_intersect((t_sphere *)node->asset_struct, ray, &t)
				&& t < closest_t)
			{
				closest_t = t;
				closest_obj = node->asset_struct;
				closest_type = node->type;
			}
		}
		if (node->type == ASS_CYLINDER)
		{
			if (cylinder_intersect((t_cylinder *)node->asset_struct, ray, &t)
				&& t < closest_t)
			{
				closest_t = t;
				closest_obj = node->asset_struct;
				closest_type = node->type;
			}
		}
		node = node->next;
	}
	if (!closest_obj)
		return (col_rgb(0, 0, 0, 0xFF));
	intersect = get_intersect(ray, closest_t);
	normal = surface_normal(closest_obj, intersect, closest_type);
	light = get_scene_light(data);
	if (!light)
		return (col_rgb(0, 0, 0, 0xFF));
	light_dir = vec_normalize(vec_sub(
		vec_new(light->pos_x, light->pos_y, light->pos_z), intersect));
	shadow_ray.origin = vec_add(intersect, vec_scale(normal, 0.001f));
	shadow_ray.direction = light_dir;
	if (is_occluded(data, shadow_ray))
		return (col_rgb(0, 0, 0, 0xFF));
	float diffuse = fmax(vec_dot(normal, light_dir), 0.0f);
	switch (closest_type)
	{
		case ASS_PLANE:
			return (col_rgb(
				((t_plane *)closest_obj)->col_r * diffuse * light->brightness,
				((t_plane *)closest_obj)->col_g * diffuse * light->brightness,
				((t_plane *)closest_obj)->col_b * diffuse * light->brightness,
				0xFF));
		case ASS_SPHERE:
			return (col_rgb(
				((t_sphere *)closest_obj)->col_r * diffuse * light->brightness,
				((t_sphere *)closest_obj)->col_g * diffuse * light->brightness,
				((t_sphere *)closest_obj)->col_b * diffuse * light->brightness,
				0xFF));
		case ASS_CYLINDER:
			return (col_rgb(
				((t_cylinder *)closest_obj)->col_r * diffuse * light->brightness,
				((t_cylinder *)closest_obj)->col_g * diffuse * light->brightness,
				((t_cylinder *)closest_obj)->col_b * diffuse * light->brightness,
				0xFF));
		default:
			return (col_rgb(0, 0, 0, 0xFF));
	}
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
	window_data.mlx_image = mlx_new_image(window_data.mlx_window, 1280, 720);
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
