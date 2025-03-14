/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgraf <jgraf@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 11:08:17 by jgraf             #+#    #+#             */
/*   Updated: 2025/03/14 12:53:36 by jgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	main(int ac, char **av)
{
	int				fd;
	t_scene_data	data;

	if (ac != 2)
		fatal_error(ERR_ARGS, NULL);
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		fatal_error(ERR_FILE, NULL);
	gc_init();
	parse_elements(&data, fd);
	close(fd);
	render_scene(&data);
	return (0);
}
