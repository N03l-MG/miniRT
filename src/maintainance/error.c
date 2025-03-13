/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmonzon <nmonzon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 18:26:09 by nmonzon           #+#    #+#             */
/*   Updated: 2025/03/13 17:51:36 by nmonzon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static char	*get_error_message(t_error error)
{
	static char	*messages[] = {
	[ERR_MEMORY] = RED "Memory allocation error." RESET,
	[ERR_ARGS] = RED "Invalid arguments. Usage: ./miniRT [.rt file/path]" RESET,
	[ERR_FILE] = RED "Could not open or read file." RESET,
	[ERR_WINDOW] = RED "Failed to create MLX window." RESET,
	[ERR_IMAGE] = RED "Failed to create MLX image." RESET,
	[ERR_DATA] = RED "Error\nScene data error." RESET,
	[ERR_AMBIENT] = RED "Error\nScene must include an ambient light." RESET,
	[ERR_CAM] = RED "Error\nScene must include a camera." RESET,
	[ERR_LIGHT] = RED "Error\nScene must have only one light object." RESET,
	[ERR_UNKNOWN] = RED "Error\nUnknown identifier: '" RESET
	};

	return (messages[error]);
}

void	error(t_error error, char *context, t_window_data *window_data)
{
	char	*message;

	message = get_error_message(error);
	if (!context)
		ft_fprintf(2, "%s\n", message);
	else
		ft_fprintf(2, "%s%s'\n", message, context);
}

void	fatal_error(t_error error, t_window_data *window_data)
{
	char	*message;

	message = get_error_message(error);
	ft_fprintf(2, "Fatal: %s\n", message);
	ft_fprintf(2, "Exiting miniRT.\n");
	clean_exit(EXIT_FAILURE, window_data);
}
