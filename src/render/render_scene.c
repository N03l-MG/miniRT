/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmonzon <nmonzon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 17:45:06 by nmonzon           #+#    #+#             */
/*   Updated: 2025/03/13 17:49:05 by nmonzon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	draw_on_image(t_scene_data *data, mlx_image_t *img)
{
	int			i;
	int			j;
	uint32_t	col = col_rgb(data->ambient->r, data->ambient->g, data->ambient->b, 0xFF);

	i = 0;
	while (i < 1280)
	{
		j = 0;
		while (j < 720)
		{
			if ((j % 20) == 0)
				col = col_rgb(data->ambient->r, data->ambient->g, data->ambient->b, 0xFF);
			mlx_put_pixel(img, i, j, col);
			j ++;
		}
		i ++;
	}
	printf("R: %i\nG: %i\nB: %i\n", get_r(col), get_g(col), get_b(col));
}

void	render_scene(t_scene_data *data)
{
	t_window_data	window_data;

	(void)data;
	window_data.mlx_window = mlx_init(1280, 720, "miniRT", false);
	if (!window_data.mlx_window)
		fatal_error(ERR_WINDOW, &window_data);
	window_data.mlx_image = mlx_new_image(window_data.mlx_window, 1280, 720);
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
