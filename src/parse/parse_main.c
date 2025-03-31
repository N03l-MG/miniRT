/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmonzon <nmonzon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 10:49:10 by jgraf             #+#    #+#             */
/*   Updated: 2025/03/31 13:04:17 by nmonzon          ###   ########.fr       */
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
		fatal_error(ERR_AMBIENT, NULL);
	else if (data->cam == NULL)
		fatal_error(ERR_CAM, NULL);
	else if (data->assets->light_cnt > 1)
		fatal_error(ERR_LIGHT, NULL);
	else if (data->assets->light_cnt < 1)
		create_dark_light(data);
}

static void	call_element(t_scene_data *data, char *line)
{
	char	**param;

	if (get_number_of_splits(line, ' ') < 1)
		return ;
	param = ft_split(line, ' ');
	if (!param)
		fatal_error(ERR_MEMORY, data->window_data);
	if (!ft_strcmp(param[0], "A"))
		parse_ambience(data, param);
	else if (!ft_strcmp(param[0], "C"))
		parse_camera(data, param);
	else if (!ft_strcmp(param[0], "L"))
		parse_light(data, param);
	else if (!ft_strcmp(param[0], "sp"))
		parse_sphere(data, param);
	else if (!ft_strcmp(param[0], "cy"))
		parse_cylinder(data, param);
	else if (!ft_strcmp(param[0], "pl"))
		parse_plane(data, param);
	else
		error(ERR_UNKNOWN, param[0]);
	free_split(param);
}

static void	scene_init(t_scene_data *data)
{
	data->ambient = NULL;
	data->cam = NULL;
	data->assets = gc_malloc(sizeof(t_assets));
	data->assets->head = NULL;
	data->assets->size = 0;
	data->assets->light_cnt = 0;
	data->assets->sphere_cnt = 0;
	data->assets->plane_cnt = 0;
	data->assets->cylinder_cnt = 0;
}

static void	pass_color_to_parent(t_assets *assets)
{
	t_asset_node	*current;

	current = assets->head;
	while (current)
	{
		if (current->type == AST_LIGHT)
			current->col = ((t_light *)current->asset_struct)->col;
		else
			assign_properties(current, current->asset_struct, current->type);
		current = current->next;
	}
}

void	parse_elements(t_scene_data *data, int fd)
{
	char	*line;
	char	*trimmed;

	line = get_next_line(fd);
	scene_init(data);
	while (line)
	{
		trimmed = ft_strtrim(line, "\n");
		if (!trimmed)
			fatal_error(ERR_MEMORY, data->window_data);
		if (ft_strncmp(line, "\n", 1) == 0)
		{
			gc_free(line);
			gc_free(trimmed);
			line = get_next_line(fd);
			continue ;
		}
		call_element(data, trimmed);
		gc_free(line);
		gc_free(trimmed);
		line = get_next_line(fd);
	}
	check_valid(data);
	printlog(LOG, "Scene setup successful.");
	pass_color_to_parent(data->assets);
}
