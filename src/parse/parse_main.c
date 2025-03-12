/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgraf <jgraf@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 10:49:10 by jgraf             #+#    #+#             */
/*   Updated: 2025/03/12 17:47:36 by jgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*	This is the main parsing part.
*	It reads through the file and calls an appropriate parsing function for
*	each element in the scene.
*	A corresponding instance of the object is added to a list or modified
*	directly in the data struct.
*/

static void	check_valid(t_scene_data *data)
{
	if (data->ambient == NULL)
		error_fatal("Error! The scene MUST contain Ambient Light!\n");
	else if (data->cam == NULL)
		error_fatal("Error! The scene MUST contain a Camera!\n");
}

static void	call_element(t_scene_data *data, char *line)
{
	char	**param;

	if (get_number_of_splits(line, ' ') < 1)
		return ;
	param = ft_split(line, ' ');
	if (ft_strncmp(param[0], "A", 1) == 0)
		parse_ambience(data, param);
	else if (ft_strncmp(param[0], "C", 1) == 0)
		parse_camera(data, param);
	else if (ft_strncmp(param[0], "L", 1) == 0)
		parse_light(data, param);
	else if (ft_strncmp(param[0], "sp", 2) == 0)
		parse_sphere(data, param);
	else if (ft_strncmp(param[0], "cy", 2) == 0)
		parse_cylinder(data, param);
	else if (ft_strncmp(param[0], "pl", 2) == 0)
		parse_plane(data, param);
	free_split(param);
}

void	parse_elements(t_scene_data *data, int fd)
{
	char	*line;
	char	*trimmed;

	line = get_next_line(fd);
	data->ambient = NULL;
	data->cam = NULL;
	data->assets = malloc(sizeof(t_assets));
	data->assets->head = NULL;
	data->assets->size = 0;
	while (line)
	{
		trimmed = ft_strtrim(line, "\n");
		if (ft_strncmp(line, "\n", 1) == 0)
		{
			free(line);
			free(trimmed);
			line = get_next_line(fd);
			continue ;
		}
		call_element(data, trimmed);
		free(line);
		free(trimmed);
		line = get_next_line(fd);
	}
	check_valid(data);
}
