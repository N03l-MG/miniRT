/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmonzon <nmonzon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:56:11 by jgraf             #+#    #+#             */
/*   Updated: 2025/03/31 12:44:46 by nmonzon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*	This is were we parse the input for Planes.
*	When there is an invalid number of splits for the corresponding section
*	or any values are out of the allowed range,
*	a warning is thrown as the plane can't be constructed.
*	The program will simply ignore this object and it will not be rendered.
*/

static bool	check_valid(t_plane *plane)
{
	if ((plane->vec_x < -1 || plane->vec_x > 1)
		|| (plane->vec_y < -1 || plane->vec_y > 1)
		|| (plane->vec_z < -1 || plane->vec_z > 1)
		|| (plane->roughness < 0 || plane->roughness > 1)
		|| (plane->reflect < 0 || plane->reflect > 1)
		|| (plane->col.r < 0 || plane->col.r > 255)
		|| (plane->col.g < 0 || plane->col.g > 255)
		|| (plane->col.b < 0 || plane->col.b > 255))
		return (printlog(WARNING, "Invalid plane object parameters"), false);
	return (true);
}

static void	add_plane(t_assets *assets, t_plane *new_plane)
{
	t_asset_node	*new_node;
	t_asset_node	*current;

	if (!check_valid(new_plane))
		return ;
	new_node = gc_malloc(sizeof(t_asset_node));
	if (!new_node)
		fatal_error(ERR_MEMORY, NULL);
	new_node->asset_struct = new_plane;
	new_node->type = AST_PLANE;
	new_node->next = NULL;
	if (assets->head == NULL)
		assets->head = new_node;
	else
	{
		current = assets->head;
		while (current->next)
			current = current->next;
		current->next = new_node;
	}
	assets->size++;
	assets->plane_cnt++;
	printlog(LOG, "Plane object setup successful.");
}

static void	set_params(t_plane *plane, char **param)
{
	plane->roughness = DEFAULT_ROUGHNESS;
	plane->reflect = DEFAULT_REFLECT;
	plane->pos_x = ft_atof(get_split_param(param[1], 0));
	plane->pos_y = ft_atof(get_split_param(param[1], 1));
	plane->pos_z = ft_atof(get_split_param(param[1], 2));
	plane->vec_x = ft_atof(get_split_param(param[2], 0));
	plane->vec_y = ft_atof(get_split_param(param[2], 1));
	plane->vec_z = ft_atof(get_split_param(param[2], 2));
	plane->col.r = ft_atoi(get_split_param(param[3], 0));
	plane->col.g = ft_atoi(get_split_param(param[3], 1));
	plane->col.b = ft_atoi(get_split_param(param[3], 2));
	if (get_number_of_split_elements(param) >= 5)
		plane->roughness = ft_atof(param[4]);
	if (get_number_of_split_elements(param) >= 6)
		plane->reflect = ft_atof(param[5]);
}

int	parse_plane(t_scene_data *data, char **param)
{
	t_plane	*new_plane;

	if (get_number_of_split_elements(param) < 5
		&& get_number_of_split_elements(param) > 6)
		return (printlog(WARNING, "Invalid plane configuration."), 0);
	if (get_number_of_splits(param[1], ',') != 3)
		return (printlog(WARNING, "Invalid plane object position."), 0);
	if (get_number_of_splits(param[2], ',') != 3)
		return (printlog(WARNING, "Invalid plane object vector."), 0);
	if (get_number_of_splits(param[3], ',') != 3)
		return (printlog(WARNING, "Invalid plane color."), 0);
	new_plane = gc_malloc(sizeof(t_plane));
	if (!new_plane)
		fatal_error(ERR_MEMORY, NULL);
	set_params(new_plane, param);
	add_plane(data->assets, new_plane);
	return (1);
}
