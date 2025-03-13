/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmonzon <nmonzon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 18:26:09 by nmonzon           #+#    #+#             */
/*   Updated: 2025/03/13 16:14:44 by nmonzon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static char	*get_error_message(t_error error)
{
	static char	*messages[] = {
	[ERR_MEMORY] = RED "Memory allocation error." RESET,
	[ERR_ARGS] = RED "Invalid arguments. Usage: ./miniRT [.rt file/path]" RESET,
	[ERR_WINDOW] = RED "Failed to create MLX window." RESET,
	[ERR_IMAGE] = RED "Failed to create MLX image." RESET,
	[ERR_DATA] = RED "Scene data error." RESET,
	};

	return (messages[error]);
}

void	error(t_error error, t_window_data *window_data)
{
	char	*message;

	message = get_error_message(error);
	ft_fprintf(2, "%s\n", message);
}

void	error_fatal(t_error error, t_window_data *window_data)
{
	char	*message;

	message = get_error_message(error);
	ft_fprintf(2, "Fatal: %s\n", message);
	ft_fprintf(2, "Exiting miniRT.\n");
	clean_exit(EXIT_FAILURE, window_data);
}

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
	exit(status);
}
