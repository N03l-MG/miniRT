/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmonzon <nmonzon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 18:26:09 by nmonzon           #+#    #+#             */
/*   Updated: 2025/03/14 16:33:22 by nmonzon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static char	*get_error_message(t_error error)
{
	static char	*messages[] = {
	[ERR_MEMORY] = "Memory allocation error.",
	[ERR_ARGS] = "Invalid arguments. Usage: ./miniRT [.rt file/path]",
	[ERR_FILE] = "Could not open or read file.",
	[ERR_WINDOW] = "Failed to create MLX window.",
	[ERR_IMAGE] = "Failed to create MLX image.",
	[ERR_DATA] = "Error\nScene data error.",
	[ERR_AMBIENT] = "Error\nScene must include an ambient light.",
	[ERR_CAM] = "Error\nScene must include a camera.",
	[ERR_LIGHT] = "Error\nScene must have only one light object.",
	[ERR_UNKNOWN] = "Error\nUnknown identifier: '"
	};

	return (messages[error]);
}

void	error(t_error error, char *context)
{
	char	*message;

	message = get_error_message(error);
	if (!context)
		ft_fprintf(2, RED "%s\n" RESET, message);
	else
		ft_fprintf(2, RED "%s%s'\n" RESET, message, context);
}

void	fatal_error(t_error error, t_window_data *window_data)
{
	char	*message;

	message = get_error_message(error);
	ft_fprintf(2, RED "Fatal: %s\n" RESET, message);
	ft_fprintf(1, "Exiting miniRT.\n");
	clean_exit(EXIT_FAILURE, window_data);
}
