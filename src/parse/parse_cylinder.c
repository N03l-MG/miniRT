/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgraf <jgraf@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:56:11 by jgraf             #+#    #+#             */
/*   Updated: 2025/03/18 16:47:43 by jgraf            ###   ########.fr       */
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
	if ((cylinder->vec_x < -1 || cylinder->vec_x > 1)
		|| (cylinder->vec_y < -1 || cylinder->vec_y > 1)
		|| (cylinder->vec_z < -1 || cylinder->vec_z > 1)
		|| (cylinder->diameter < 0)
		|| (cylinder->height < 0))
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
	cylinder->pos_x = ft_atof(get_split_param(param[1], 0));
	cylinder->pos_y = ft_atof(get_split_param(param[1], 1));
	cylinder->pos_z = ft_atof(get_split_param(param[1], 2));
	cylinder->vec_x = ft_atof(get_split_param(param[2], 0));
	cylinder->vec_y = ft_atof(get_split_param(param[2], 1));
	cylinder->vec_z = ft_atof(get_split_param(param[2], 2));
	cylinder->diameter = ft_atof(param[3]);
	cylinder->height = ft_atof(param[4]);
	cylinder->col.r = ft_atoi(get_split_param(param[5], 0));
	cylinder->col.g = ft_atoi(get_split_param(param[5], 1));
	cylinder->col.b = ft_atoi(get_split_param(param[5], 2));
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
