/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgraf <jgraf@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:56:11 by jgraf             #+#    #+#             */
/*   Updated: 2025/03/14 08:17:01 by jgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*	This is were we parse the input for Cylinders.
*	When there is an invalid number of splits for the corresponding section
*	or any values are out of the allowed range,
*	a warning is thrown as the cylinder can't be constructed.
*	The program will simply ignore this object and it will not be rendered.
*/

static bool	check_valid(t_cylinder *cylinder)
{
	if ((cylinder->vx < -1 || cylinder->vx > 1)
		|| (cylinder->vy < -1 || cylinder->vy > 1)
		|| (cylinder->vz < -1 || cylinder->vz > 1)
		|| (cylinder->r < 0 || cylinder->r > 255)
		|| (cylinder->g < 0 || cylinder->g > 255)
		|| (cylinder->b < 0 || cylinder->b > 255)
		|| (cylinder->d < 0)
		|| (cylinder->h < 0))
		return (printlog(WARNING, "Invalid cylinder object parameters"), false);
	return (true);
}

static void	add_cylinder(t_assets *assets, t_cylinder *new_cylinder)
{
	t_asset_node	*new_node;
	t_asset_node	*current;

	if (!check_valid(new_cylinder))
		return ;
	new_node = gc_malloc(sizeof(t_asset_node));
	new_node->asset_struct = new_cylinder;
	new_node->type = ASS_CYLINDER;
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
	assets->cylinder_cnt ++;
	printlog(LOG, "Cylinder object setup successful.");
}

static void	set_params(t_cylinder *cylinder, char **param)
{
	cylinder->x = ft_atof(get_split_param(param[1], 0));
	cylinder->y = ft_atof(get_split_param(param[1], 1));
	cylinder->z = ft_atof(get_split_param(param[1], 2));
	cylinder->vx = ft_atof(get_split_param(param[2], 0));
	cylinder->vy = ft_atof(get_split_param(param[2], 1));
	cylinder->vz = ft_atof(get_split_param(param[2], 2));
	cylinder->d = ft_atof(param[3]);
	cylinder->h = ft_atof(param[4]);
	cylinder->r = ft_atoi(get_split_param(param[5], 0));
	cylinder->g = ft_atoi(get_split_param(param[5], 1));
	cylinder->b = ft_atoi(get_split_param(param[5], 2));
}

int	parse_cylinder(t_scene_data *data, char **param)
{
	t_cylinder	*new_cylinder;

	if (get_number_of_split_elements(param) != 6)
		return (printlog(WARNING, "Invalid cylinder configuration."), 0);
	if (get_number_of_splits(param[1], ',') != 3)
		return (printlog(WARNING, "Invalid cylinder object position."), 0);
	if (get_number_of_splits(param[2], ',') != 3)
		return (printlog(WARNING, "Invalid cylinder object vector."), 0);
	if (get_number_of_splits(param[5], ',') != 3)
		return (printlog(WARNING, "Invalid cylinder color."), 0);
	new_cylinder = gc_malloc(sizeof(t_cylinder));
	set_params(new_cylinder, param);
	add_cylinder(data->assets, new_cylinder);
	return (1);
}
