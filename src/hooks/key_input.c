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

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_scene_data	*data;
	double			current_time;

	data = (t_scene_data *)param;
	current_time = mlx_get_time();
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		clean_exit(EXIT_SUCCESS, data->window_data);
	if (current_time - data->window_data->last_render < 1.0 / 30.0
		|| data->window_data->is_rendering)
		return ;
	if (translation_keys(keydata, data)
		|| rotation_keys(keydata, data)
		|| sample_keys(keydata, data))
	{
		camera_setup(data->cam);
		draw_frame(data, data->window_data->mlx_image);
	}
	data->window_data->last_render = current_time;
}
