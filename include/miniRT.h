/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmonzon <nmonzon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 11:05:08 by jgraf             #+#    #+#             */
/*   Updated: 2025/03/11 18:49:37 by nmonzon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

//	Libraries
# include "../libft/include/libft.h"
# include "structs.h"
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>

# define RED "\001\033[0;31m\002"
# define RESET "\001\033[0m\002"

# define WIDTH 1080;
# define HEIGHT 720;

//	Functions
void	parse_elements(t_scene_data *data, int fd);

void	handle_error(t_error error, t_window_data *window_data);
void	clean_exit(int status, t_window_data *window_data);


#endif