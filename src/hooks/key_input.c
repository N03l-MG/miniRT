/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgraf <jgraf@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 08:31:21 by jgraf             #+#    #+#             */
/*   Updated: 2025/03/24 15:24:22 by jgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	escape_key(mlx_key_data_t keydata, t_window_data *window_data)
{
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		clean_exit(EXIT_SUCCESS, window_data);
}

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_scene_data	*data;

	data = (t_scene_data *)param;
	escape_key(keydata, data->window_data);
	if (translation_keys(keydata, data)
		|| rotation_keys(keydata, data)
		|| sample_keys(keydata, data))
	{
		camera_setup(data->cam);
		draw_frame(data, data->window_data->mlx_image);
	}
}
