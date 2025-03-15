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

static uint32_t	ray_color(t_scene_data *data, t_ray ray)
{
	t_asset_node	*node;
	double			t;
	double			closest_t;
	void			*closest_obj;
	t_asset_type	closest_type;

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
	switch (closest_type)
	{
		case ASS_PLANE:
			return (col_rgb(((t_plane *)closest_obj)->col_r,
						((t_plane *)closest_obj)->col_g,
						((t_plane *)closest_obj)->col_b, 0xFF));
		case ASS_SPHERE:
			return (col_rgb(((t_sphere *)closest_obj)->col_r,
						((t_sphere *)closest_obj)->col_g,
						((t_sphere *)closest_obj)->col_b, 0xFF));
		case ASS_CYLINDER:
			return (col_rgb(((t_cylinder *)closest_obj)->col_r,
						((t_cylinder *)closest_obj)->col_g,
						((t_cylinder *)closest_obj)->col_b, 0xFF));
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
			mlx_put_pixel(img, i, j, ray_color(data, ray));
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
