/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgraf <jgraf@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:56:11 by jgraf             #+#    #+#             */
/*   Updated: 2025/03/12 17:13:13 by jgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*	This is were we parse the input for Planes.
*	When there is an invalid number of splits for the corresponding section
*	or any values are out of the allowed range,
*	a warning is thrown as the plane can't be constructed.
*	The program will simply irgnore this object and it will not be rendered.
*/

static bool	check_valid(t_plane *plane)
{
	if ((plane->vx < -1 || plane->vx > 1)
		|| (plane->vy < -1 || plane->vy > 1)
		|| (plane->vz < -1 || plane->vz > 1)
		|| (plane->r < 0 || plane->r > 255)
		|| (plane->g < 0 || plane->g > 255)
		|| (plane->b < 0 || plane->b > 255))
	{
		printf("Warning! Parameters out of bounds for a Plane\n");
		return (false);
	}
	return (true);
}

static void	add_plane(t_assets *assets, t_plane *new_plane)
{
	t_asset_node	*new_node;
	t_asset_node	*current;

	if (!check_valid(new_plane))
		return ;
	new_node = malloc(sizeof(t_asset_node));
	new_node->asset_struct = new_plane;
	new_node->type = ASS_PLANE;
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
	assets->size ++;
}

static void	set_params(t_plane *plane, char **param)
{
	plane->x = ft_atof(get_split_param(param[1], 0));
	plane->y = ft_atof(get_split_param(param[1], 1));
	plane->z = ft_atof(get_split_param(param[1], 2));
	plane->vx = ft_atof(get_split_param(param[2], 0));
	plane->vy = ft_atof(get_split_param(param[2], 1));
	plane->vz = ft_atof(get_split_param(param[2], 2));
	plane->r = ft_atoi(get_split_param(param[3], 0));
	plane->g = ft_atoi(get_split_param(param[3], 1));
	plane->b = ft_atoi(get_split_param(param[3], 2));
}

int	parse_plane(t_scene_data *data, char **param)
{
	t_plane	*new_plane;

	if (get_number_of_split_elements(param) != 4)
		return (error("Warning! Invalid config for a Plane object\n"), 0);
	if (get_number_of_splits(param[1], ',') != 3)
		return (error("Warning! Invalid position for a Plane object\n"), 0);
	if (get_number_of_splits(param[2], ',') != 3)
		return (error("Warning! Invalid vector for a Plane object\n"), 0);
	if (get_number_of_splits(param[3], ',') != 3)
		return (error("Warning! Invalid color for a Plane object\n"), 0);
	new_plane = malloc(sizeof(t_plane));
	set_params(new_plane, param);
	add_plane(data->assets, new_plane);
	return (1);
}
