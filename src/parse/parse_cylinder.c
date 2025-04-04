/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmonzon <nmonzon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:56:11 by jgraf             #+#    #+#             */
/*   Updated: 2025/03/31 12:43:25 by nmonzon          ###   ########.fr       */
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
		|| (cylinder->height < 0)
		|| (cylinder->roughness < 0 || cylinder->roughness > 1)
		|| (cylinder->reflect < 0 || cylinder->reflect > 1)
		|| (cylinder->col.r < 0 || cylinder->col.r > 255)
		|| (cylinder->col.g < 0 || cylinder->col.g > 255)
		|| (cylinder->col.b < 0 || cylinder->col.b > 255))
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
	if (!new_node)
		fatal_error(ERR_MEMORY, NULL);
	new_node->asset_struct = new_cylinder;
	new_node->type = AST_CYLINDER;
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
	assets->cylinder_cnt++;
	printlog(LOG, "Cylinder object setup successful.");
}

static void	set_params(t_cylinder *cylinder, char **param)
{
	cylinder->roughness = DEFAULT_ROUGHNESS;
	cylinder->reflect = DEFAULT_REFLECT;
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
	if (get_number_of_split_elements(param) >= 7)
		cylinder->roughness = ft_atof(param[6]);
	if (get_number_of_split_elements(param) >= 8)
		cylinder->reflect = ft_atof(param[7]);
}

int	parse_cylinder(t_scene_data *data, char **param)
{
	t_cylinder	*new_cylinder;

	if (get_number_of_split_elements(param) < 7
		&& get_number_of_split_elements(param) > 8)
		return (printlog(WARNING, "Invalid cylinder configuration."), 0);
	if (get_number_of_splits(param[1], ',') != 3)
		return (printlog(WARNING, "Invalid cylinder object position."), 0);
	if (get_number_of_splits(param[2], ',') != 3)
		return (printlog(WARNING, "Invalid cylinder object vector."), 0);
	if (get_number_of_splits(param[5], ',') != 3)
		return (printlog(WARNING, "Invalid cylinder color."), 0);
	new_cylinder = gc_malloc(sizeof(t_cylinder));
	if (!new_cylinder)
		fatal_error(ERR_MEMORY, NULL);
	set_params(new_cylinder, param);
	add_cylinder(data->assets, new_cylinder);
	return (1);
}
