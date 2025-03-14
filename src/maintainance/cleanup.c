/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgraf <jgraf@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 17:43:08 by nmonzon           #+#    #+#             */
/*   Updated: 2025/03/14 08:42:29 by jgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	clean_exit(int status, t_window_data *window_data)
{
	if (window_data)
	{
		if (window_data->mlx_image)
			mlx_delete_image(window_data->mlx_window, window_data->mlx_image);
		if (window_data->mlx_window)
			mlx_terminate(window_data->mlx_window);
	}
	gc_collect();
	system("leaks miniRT");
	exit(status);
}
