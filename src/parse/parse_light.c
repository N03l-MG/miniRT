/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgraf <jgraf@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:56:11 by jgraf             #+#    #+#             */
/*   Updated: 2025/03/12 17:13:03 by jgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*	This is were we parse the input for the Light.
*	When there is an invalid number of splits for the corresponding section,
*	a fatal error is thrown as the light can't be constructed, but the
*	program needs a properly constructed light.
*/

static bool	check_valid(t_light *light)
{
	if ((light->r < 0 || light->r > 255)
		|| (light->g < 0 || light->g > 255)
		|| (light->b < 0 || light->b > 255)
		|| (light->brightness < 0 || light->brightness > 1))
	{
		printf("Warning! Parameters out of bounds for a Light\n");
		return (false);
	}
	return (true);
}

static void	add_light(t_assets *assets, t_light *new_light)
{
	t_asset_node	*new_node;
	t_asset_node	*current;

	if (!check_valid(new_light))
		return ;
	new_node = malloc(sizeof(t_asset_node));
	new_node->asset_struct = new_light;
	new_node->type = ASS_LIGHT;
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

static void	set_params(t_light *light, char **param)
{
	light->x = ft_atof(get_split_param(param[1], 0));
	light->y = ft_atof(get_split_param(param[1], 1));
	light->z = ft_atof(get_split_param(param[1], 2));
	light->brightness = ft_atof(param[2]);
	light->r = ft_atoi(get_split_param(param[3], 0));
	light->g = ft_atoi(get_split_param(param[3], 1));
	light->b = ft_atoi(get_split_param(param[3], 2));
}

int	parse_light(t_scene_data *data, char **param)
{
	t_light	*new_light;

	if (get_number_of_split_elements(param) != 4)
		return (error("Warning! Invalid config for a Light\n"), 0);
	if (get_number_of_splits(param[1], ',') != 3)
		return (error("Warning! Invalid position for a Light object\n"), 0);
	if (get_number_of_splits(param[3], ',') != 3)
		return (error("Warning! Invalid color for a Light object\n"), 0);
	new_light = malloc(sizeof(t_light));
	set_params(new_light, param);
	add_light(data->assets, new_light);
	return (1);
}
