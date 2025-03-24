/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sample_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgraf <jgraf@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 09:37:57 by jgraf             #+#    #+#             */
/*   Updated: 2025/03/24 09:39:26 by jgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

bool	sample_keys(mlx_key_data_t keydata, t_scene_data *data)
{
	short	m;

	m = 16;
	if (keydata.key == MLX_KEY_KP_ADD
		&& (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		if (data->samples < 112)
			data->samples += m;
	}
	else if (keydata.key == MLX_KEY_KP_SUBTRACT
		&& (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		if (data->samples > 1)
			data->samples -= m;
	}
	else
		return (false);
	if (data->samples % m != 0)
		data->samples = round(data->samples / m) * m;
	if (data->samples <= 0)
		data->samples = 1;
	if (data->samples >= 112)
		data->samples = 112;
	printf(MAGENTA "Log: Shadow samples set to %i\n" RESET, data->samples);
	return (true);
}
