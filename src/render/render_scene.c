/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgraf <jgraf@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 17:45:06 by nmonzon           #+#    #+#             */
/*   Updated: 2025/03/14 13:03:41 by jgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	draw_on_image(t_scene_data *data, mlx_image_t *img)
{
	int			i;
	int			j;
	uint32_t	basecol = col_rgb(data->ambient->r, data->ambient->g, data->ambient->b, 0xFF);
	uint32_t	col = basecol;

	i = 0;
	while (i < WIDTH)
	{
		j = 0;
		while (j < HEIGHT)
		{
			if (i % 6 == 0)
			{
				if (j % 6 == 0)
					col = col_rgb(get_r(basecol), 0, 0, 0xFF);
				if (j % 12 == 0)
					col = col_rgb(0, get_g(basecol), 0, 0xFF);
				if (j % 18 == 0)
					col = col_rgb(0, 0, get_b(basecol), 0xFF);
			}
			mlx_put_pixel(img, i, j, col);
			j ++;
		}
		i ++;
	}
}

void	render_scene(t_scene_data *data)
{
	t_window_data	window_data;

	(void)data;
	window_data.mlx_window = mlx_init(WIDTH, HEIGHT, "miniRT", false);
	if (!window_data.mlx_window)
		fatal_error(ERR_WINDOW, &window_data);
	window_data.mlx_image = mlx_new_image(window_data.mlx_window, WIDTH, HEIGHT);
	if (!window_data.mlx_image)
		fatal_error(ERR_IMAGE, &window_data);
	window_data.image_data = (unsigned char *)window_data.mlx_image->pixels;
	if (!window_data.image_data)
		fatal_error(ERR_DATA, &window_data);
	draw_on_image(data, window_data.mlx_image);
	mlx_image_to_window(window_data.mlx_window, window_data.mlx_image, 0, 0);
	mlx_key_hook(window_data.mlx_window, &escape_key, window_data.mlx_window);
	mlx_loop(window_data.mlx_window);
	clean_exit(EXIT_SUCCESS, &window_data);
}
