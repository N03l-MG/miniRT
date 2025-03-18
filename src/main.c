/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgraf <jgraf@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 11:08:17 by jgraf             #+#    #+#             */
/*   Updated: 2025/03/18 13:34:46 by jgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static bool	check_file_format(char *file)
{
	int	len;

	len = ft_strlen(file);
	if (len < 3)
		return (true);
	if (file[len - 3] == '.' && file[len - 2] == 'r' && file[len - 1] == 't')
		return (false);
	return (true);
}

int	main(int ac, char **av)
{
	int				fd;
	t_scene_data	data;

	if (ac != 2 || check_file_format(av[1]))
		fatal_error(ERR_ARGS, NULL);
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		fatal_error(ERR_FILE, NULL);
	parse_elements(&data, fd);
	close(fd);
	render_scene(&data);
	return (0);
}
