/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logging.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgraf <jgraf@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 17:04:11 by nmonzon           #+#    #+#             */
/*   Updated: 2025/03/21 16:04:27 by jgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	printlog(t_log_type log_type, char *message)
{
	if (log_type == LOG)
		ft_fprintf(1, MAGENTA "Log: %s\n" RESET, message);
	else if (log_type == WARNING)
		ft_fprintf(1, YELLOW "Error:\n%s\n" RESET, message);
}
