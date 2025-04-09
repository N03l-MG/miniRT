/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgraf <jgraf@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 18:26:09 by kixik             #+#    #+#             */
/*   Updated: 2025/03/25 10:52:29 by jgraf            ###   ########.fr       */
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
	[ERR_DATA] = "Error: Scene data error.",
	[ERR_AMBIENT] = "Error: Scene must include an ambient light.",
	[ERR_CAM] = "Error: Scene must include a camera.",
	[ERR_LIGHT] = "Error: Scene may only contain one light object.",
	[ERR_UNKNOWN] = "Error: Unknown identifier: '",
	[ERR_OBJFILE] = "Failed to read Wavefront obj file."
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
	clean_exit(EXIT_FAILURE, window_data);
}
