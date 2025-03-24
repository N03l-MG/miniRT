/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgraf <jgraf@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 09:26:32 by jgraf             #+#    #+#             */
/*   Updated: 2025/03/24 09:36:18 by jgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static bool	sideways(mlx_key_data_t keydata, t_scene_data *data, float rot_spd)
{
	if (keydata.key == MLX_KEY_RIGHT
		&& (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		data->cam->vec_z
			= data->cam->vec_x * sin(rot_spd) + data->cam->vec_z * cos(rot_spd);
		data->cam->vec_x
			= data->cam->vec_x * cos(rot_spd) - data->cam->vec_z * sin(rot_spd);
	}
	else if (keydata.key == MLX_KEY_LEFT
		&& (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		data->cam->vec_z = data->cam->vec_x * sin(-rot_spd)
			+ data->cam->vec_z * cos(-rot_spd);
		data->cam->vec_x = data->cam->vec_x * cos(-rot_spd)
			- data->cam->vec_z * sin(-rot_spd);
	}
	else
		return (false);
	return (true);
}

static bool	up_down(mlx_key_data_t keydata, t_scene_data *data, float rot_spd)
{
	if (keydata.key == MLX_KEY_UP
		&& (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		if (data->cam->vec_y < 0.95f)
			data->cam->vec_y += rot_spd;
	}
	else if (keydata.key == MLX_KEY_DOWN
		&& (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		if (data->cam->vec_y > -0.95f)
			data->cam->vec_y -= rot_spd;
	}
	else
		return (false);
	return (true);
}

bool	rotation_keys(mlx_key_data_t keydata, t_scene_data *data)
{
	float	rot_spd;
	float	len;

	rot_spd = 0.05f;
	if (sideways(keydata, data, rot_spd) || up_down(keydata, data, rot_spd))
	{
		len = sqrt(data->cam->vec_x * data->cam->vec_x
				+ data->cam->vec_y * data->cam->vec_y
				+ data->cam->vec_z * data->cam->vec_z);
		data->cam->vec_x /= len;
		data->cam->vec_y /= len;
		data->cam->vec_z /= len;
		return (true);
	}
	return (false);
}
