/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgraf <jgraf@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 11:08:17 by jgraf             #+#    #+#             */
/*   Updated: 2025/03/24 08:40:26 by jgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static bool	check_file_format(char *file)
{
	char	*result;
	int		len;

	len = ft_strlen(file);
	if (len < 3)
		return (true);
	result = ft_substr(file, len - 3, 3);
	if (!result)
		return (true);
	if (ft_strcmp(".rt", result) == 0)
		return (gc_free(result), false);
	return (gc_free(result), true);
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
	data.samples = SHDW_SAMPLES;
	render_scene(&data);
	return (0);
}
