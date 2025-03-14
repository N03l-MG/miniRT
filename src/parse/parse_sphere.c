/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgraf <jgraf@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:56:11 by jgraf             #+#    #+#             */
/*   Updated: 2025/03/14 14:19:42 by jgraf            ###   ########.fr       */
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
	if ((sphere->col_r < 0 || sphere->col_r > 255)
		|| (sphere->col_g < 0 || sphere->col_g > 255)
		|| (sphere->col_b < 0 || sphere->col_b > 255)
		|| (sphere->diameter < 0))
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
	new_node->asset_struct = new_sphere;
	new_node->type = ASS_SPHERE;
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
	assets->sphere_cnt ++;
	printlog(LOG, "Sphere object setup successful.");
}

static void	set_params(t_sphere *sphere, char **param)
{
	sphere->pos_x = ft_atof(get_split_param(param[1], 0));
	sphere->pos_y = ft_atof(get_split_param(param[1], 1));
	sphere->pos_z = ft_atof(get_split_param(param[1], 2));
	sphere->diameter = ft_atof(param[2]);
	sphere->col_r = ft_atoi(get_split_param(param[3], 0));
	sphere->col_g = ft_atoi(get_split_param(param[3], 1));
	sphere->col_b = ft_atoi(get_split_param(param[3], 2));
}

int	parse_sphere(t_scene_data *data, char **param)
{
	t_sphere	*new_sphere;

	if (get_number_of_split_elements(param) != 4)
		return (printlog(WARNING, "Invalid sphere configuration."), 0);
	if (get_number_of_splits(param[1], ',') != 3)
		return (printlog(WARNING, "Invalid sphere object position."), 0);
	if (get_number_of_splits(param[3], ',') != 3)
		return (printlog(WARNING, "Invalid sphere color."), 0);
	new_sphere = gc_malloc(sizeof(t_sphere));
	set_params(new_sphere, param);
	add_sphere(data->assets, new_sphere);
	return (1);
}
