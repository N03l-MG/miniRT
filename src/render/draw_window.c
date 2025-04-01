/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgraf <jgraf@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 11:49:30 by jgraf             #+#    #+#             */
/*   Updated: 2025/03/24 16:01:24 by jgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	draw_frame(t_scene_data *data, mlx_image_t *img)
{
	int		i;
	int		j;
	t_ray	ray;
	int		current_pixel;
	int		last_percentage;

	camera_setup(data->cam);
	current_pixel = 0;
	last_percentage = 0;
	data->window_data->is_rendering = true;
	i = -1;
	while (++i < HEIGHT)
	{
		j = -1;
		while (++j < WIDTH)
		{
			ray = camera_ray_for_pixel(data->cam, j, i);
			mlx_put_pixel(img, j, i, trace_ray(data, ray, 0));
			current_pixel++;
			if ((current_pixel * 100 / TOTAL_PIXELS) >= last_percentage + 10)
			{
				last_percentage = (current_pixel * 100 / TOTAL_PIXELS);
				printf(MAGENTA "Log: Rendering [ %d%% ]\n" RESET, last_percentage);
			}
		}
	}
	data->window_data->is_rendering = false;
	printlog(LOG, "Rendering complete!");
}

void	render_scene(t_scene_data *data)
{
	t_window_data	window_data;

	window_data.mlx_window = mlx_init(WIDTH, HEIGHT, "miniRT", false);
	if (!window_data.mlx_window)
		fatal_error(ERR_WINDOW, &window_data);
	window_data.mlx_image
		= mlx_new_image(window_data.mlx_window, WIDTH, HEIGHT);
	if (!window_data.mlx_image)
		fatal_error(ERR_IMAGE, &window_data);
	window_data.image_data = (unsigned char *)window_data.mlx_image->pixels;
	if (!window_data.image_data)
		fatal_error(ERR_DATA, &window_data);
	data->window_data = &window_data;
	window_data.last_render = mlx_get_time();
	window_data.is_rendering = false;
	draw_frame(data, window_data.mlx_image);
	mlx_image_to_window(window_data.mlx_window, window_data.mlx_image, 0, 0);
	mlx_key_hook(window_data.mlx_window, &key_hook, data);
	mlx_loop(window_data.mlx_window);
	clean_exit(EXIT_SUCCESS, &window_data);
}
