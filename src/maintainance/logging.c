/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logging.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmonzon <nmonzon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 17:04:11 by nmonzon           #+#    #+#             */
/*   Updated: 2025/03/17 12:43:04 by nmonzon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	printlog(t_log_type log_type, char *message)
{
	if (log_type == LOG)
		ft_fprintf(1, MAGENTA "Log: %s\n" RESET, message);
	else if (log_type == WARNING)
		ft_fprintf(1, YELLOW "Warning: %s\n" RESET, message);
}
