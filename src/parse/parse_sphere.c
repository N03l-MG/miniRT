/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmonzon <nmonzon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:56:11 by jgraf             #+#    #+#             */
/*   Updated: 2025/03/31 12:45:20 by nmonzon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*	This is were we parse the input for Spheres.
*	When there is an invalid number of splits for the corresponding section
*	or any values are out of the allowed range,
*	a warning is thrown as the sphere can't be constructed.
*	The program will simply ignore this object and it will not be rendered.
*/

static bool	check_valid(t_sphere *sphere)
{
	if ((sphere->diameter < 0)
		|| (sphere->roughness < 0 || sphere->roughness > 1)
		|| (sphere->reflect < 0 || sphere->reflect > 1)
		|| (sphere->col.r < 0 || sphere->col.r > 255)
		|| (sphere->col.g < 0 || sphere->col.g > 255)
		|| (sphere->col.b < 0 || sphere->col.b > 255))
		return (printlog(WARNING, "Invalid sphere object parameters"), false);
	return (true);
}

static void	add_sphere(t_assets *assets, t_sphere *new_sphere)
{
	t_asset_node	*new_node;
	t_asset_node	*current;

	if (!check_valid(new_sphere))
		return ;
	new_node = gc_malloc(sizeof(t_asset_node));
	if (!new_node)
		fatal_error(ERR_MEMORY, NULL);
	new_node->asset_struct = new_sphere;
	new_node->type = AST_SPHERE;
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
	assets->sphere_cnt++;
	printlog(LOG, "Sphere object setup successful.");
}

static void	set_params(t_sphere *sphere, char **param)
{
	sphere->roughness = DEFAULT_ROUGHNESS;
	sphere->reflect = DEFAULT_REFLECT;
	sphere->pos_x = ft_atof(get_split_param(param[1], 0));
	sphere->pos_y = ft_atof(get_split_param(param[1], 1));
	sphere->pos_z = ft_atof(get_split_param(param[1], 2));
	sphere->diameter = ft_atof(param[2]);
	sphere->col.r = ft_atoi(get_split_param(param[3], 0));
	sphere->col.g = ft_atoi(get_split_param(param[3], 1));
	sphere->col.b = ft_atoi(get_split_param(param[3], 2));
	if (get_number_of_split_elements(param) >= 5)
		sphere->roughness = ft_atof(param[4]);
	if (get_number_of_split_elements(param) >= 6)
		sphere->reflect = ft_atof(param[5]);
}

int	parse_sphere(t_scene_data *data, char **param)
{
	t_sphere	*new_sphere;

	if (get_number_of_split_elements(param) < 5
		&& get_number_of_split_elements(param) > 6)
		return (printlog(WARNING, "Invalid sphere configuration."), 0);
	if (get_number_of_splits(param[1], ',') != 3)
		return (printlog(WARNING, "Invalid sphere object position."), 0);
	if (get_number_of_splits(param[3], ',') != 3)
		return (printlog(WARNING, "Invalid sphere color."), 0);
	new_sphere = gc_malloc(sizeof(t_sphere));
	if (!new_sphere)
		fatal_error(ERR_MEMORY, NULL);
	set_params(new_sphere, param);
	add_sphere(data->assets, new_sphere);
	return (1);
}
