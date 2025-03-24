/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translation_input.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgraf <jgraf@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 09:12:26 by jgraf             #+#    #+#             */
/*   Updated: 2025/03/24 09:25:23 by jgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static bool	up_down(mlx_key_data_t keydata, t_scene_data *data, float move_spd)
{
	if (keydata.key == MLX_KEY_W
		&& (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		data->cam->pos_z += data->cam->vec_z * move_spd;
		data->cam->pos_x += data->cam->vec_x * move_spd;
		data->cam->pos_y += data->cam->vec_y * move_spd;
	}
	else if (keydata.key == MLX_KEY_S
		&& (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		data->cam->pos_z -= data->cam->vec_z * move_spd;
		data->cam->pos_x -= data->cam->vec_x * move_spd;
		data->cam->pos_y -= data->cam->vec_y * move_spd;
	}
	else
		return (false);
	return (true);
}

static bool	strafe(mlx_key_data_t keydata, t_scene_data *data, float move_spd)
{
	t_vector	up;
	t_vector	strafe;
	t_vector	forward;

	up = vec_new(0, 1, 0);
	forward = vec_new(data->cam->vec_x, data->cam->vec_y, data->cam->vec_z);
	strafe = vec_normalize(vec_cross(forward, up));
	if (keydata.key == MLX_KEY_A
		&& (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		data->cam->pos_x -= strafe.x * move_spd;
		data->cam->pos_y -= strafe.y * move_spd;
		data->cam->pos_z -= strafe.z * move_spd;
	}
	else if (keydata.key == MLX_KEY_D
		&& (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		data->cam->pos_x += strafe.x * move_spd;
		data->cam->pos_y += strafe.y * move_spd;
		data->cam->pos_z += strafe.z * move_spd;
	}
	else
		return (false);
	return (true);
}

bool	translation_keys(mlx_key_data_t keydata, t_scene_data *data)
{
	float		move_spd;

	move_spd = 0.8f;
	if (up_down(keydata, data, move_spd) || strafe(keydata, data, move_spd))
		return (true);
	return (false);
}
