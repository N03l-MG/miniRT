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

	camera_setup(data->cam);
	i = -1;
	while (++i < HEIGHT)
	{
		j = -1;
		while (++j < WIDTH)
		{
			ray = camera_ray_for_pixel(data->cam, j, i);
			mlx_put_pixel(img, j, i, trace_ray(data, ray, 0));
		}
	}
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
	draw_frame(data, window_data.mlx_image);
	mlx_image_to_window(window_data.mlx_window, window_data.mlx_image, 0, 0);
	mlx_key_hook(window_data.mlx_window, &key_hook, data);
	mlx_loop(window_data.mlx_window);
	clean_exit(EXIT_SUCCESS, &window_data);
}
