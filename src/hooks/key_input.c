/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmonzon <nmonzon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 08:31:21 by jgraf             #+#    #+#             */
/*   Updated: 2025/03/19 17:48:53 by nmonzon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	escape_key(mlx_key_data_t keydata, t_window_data *window_data)
{
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		clean_exit(EXIT_SUCCESS, window_data);
}

static bool	translation_keys(mlx_key_data_t keydata, t_scene_data *data)
{
	float		move_speed = 0.8f;
	t_vector	up = vec_new(0, 1, 0);
	t_vector	forward;
	t_vector	strafe;

	forward = vec_new(data->cam->vec_x, data->cam->vec_y, data->cam->vec_z);
	strafe = vec_normalize(vec_cross(forward, up));
	if (keydata.key == MLX_KEY_W && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		data->cam->pos_z += data->cam->vec_z * move_speed;
		data->cam->pos_x += data->cam->vec_x * move_speed;
		data->cam->pos_y += data->cam->vec_y * move_speed;
	}
	else if (keydata.key == MLX_KEY_S && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		data->cam->pos_z -= data->cam->vec_z * move_speed;
		data->cam->pos_x -= data->cam->vec_x * move_speed;
		data->cam->pos_y -= data->cam->vec_y * move_speed;
	}
	else if (keydata.key == MLX_KEY_A && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		data->cam->pos_x -= strafe.x * move_speed;
		data->cam->pos_y -= strafe.y * move_speed;
		data->cam->pos_z -= strafe.z * move_speed;
	}
	else if (keydata.key == MLX_KEY_D && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		data->cam->pos_x += strafe.x * move_speed;
		data->cam->pos_y += strafe.y * move_speed;
		data->cam->pos_z += strafe.z * move_speed;
	}
	else
		return (false);
	return (true);
}

static bool	rotation_keys(mlx_key_data_t keydata, t_scene_data *data)
{
	float	rotate_speed = 0.05f;
	float	old_x;
	float	len;

	if (keydata.key == MLX_KEY_RIGHT && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		old_x = data->cam->vec_x;
		data->cam->vec_x = data->cam->vec_x * cos(rotate_speed) - data->cam->vec_z * sin(rotate_speed);
		data->cam->vec_z = old_x * sin(rotate_speed) + data->cam->vec_z * cos(rotate_speed);
	}
	else if (keydata.key == MLX_KEY_LEFT && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		old_x = data->cam->vec_x;
		data->cam->vec_x = data->cam->vec_x * cos(-rotate_speed) - data->cam->vec_z * sin(-rotate_speed);
		data->cam->vec_z = old_x * sin(-rotate_speed) + data->cam->vec_z * cos(-rotate_speed);
	}
	else if (keydata.key == MLX_KEY_UP && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		if (data->cam->vec_y < 0.95f)
			data->cam->vec_y += rotate_speed;
	}
	else if (keydata.key == MLX_KEY_DOWN && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		if (data->cam->vec_y > -0.95f)
			data->cam->vec_y -= rotate_speed;
	}
	else
		return (false);
	len = sqrt(data->cam->vec_x * data->cam->vec_x
				+ data->cam->vec_y * data->cam->vec_y
				+ data->cam->vec_z * data->cam->vec_z);
	data->cam->vec_x /= len;
	data->cam->vec_y /= len;
	data->cam->vec_z /= len;
	return (true);
}

static bool	sample_keys(mlx_key_data_t keydata, t_scene_data *data)
{
	if (keydata.key == MLX_KEY_KP_ADD && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		if (data->samples < 112)
			data->samples += 16;
	}
	else if (keydata.key == MLX_KEY_KP_SUBTRACT && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		if (data->samples > 1)
			data->samples -= 16;
	}
	else
		return (false);
	if (data->samples % 16 != 0)
		data->samples = round(data->samples / 16) * 16;
	if (data->samples <= 0)
		data->samples = 1;
	printf(MAGENTA "Log: Shadow samples set to %i\n" RESET, data->samples);
	return (true);
}

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_scene_data *data = (t_scene_data*)param;

	escape_key(keydata, data->window_data);
	if (translation_keys(keydata, data)
		|| rotation_keys(keydata, data)
		|| sample_keys(keydata, data))
	{
		camera_setup(data->cam);
		draw_frame(data, data->window_data->mlx_image);
	}
}
