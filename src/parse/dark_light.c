/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dark_light.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmonzon <nmonzon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:56:11 by jgraf             #+#    #+#             */
/*   Updated: 2025/03/31 13:04:40 by nmonzon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*	This is were we create a light that has a luminance of 0.
*	This allows for an undeclared light object that exists, but has no
*	effect on the scene. This holds the rendering and lighting code clean.
*/

static void	add_light(t_assets *assets, t_light *new_light)
{
	t_asset_node	*new_node;
	t_asset_node	*current;

	new_node = gc_malloc(sizeof(t_asset_node));
	if (!new_node)
		fatal_error(ERR_MEMORY, NULL);
	new_node->asset_struct = new_light;
	new_node->type = AST_LIGHT;
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
	assets->light_cnt ++;
	printlog(LOG, "No Light found... Resorting to Darklight.");
}

static void	set_params(t_light *light)
{
	light->pos_x = 0;
	light->pos_y = 0;
	light->pos_z = 0;
	light->brightness = 0;
	light->col.r = 0;
	light->col.g = 0;
	light->col.b = 0;
}

int	create_dark_light(t_scene_data *data)
{
	t_light	*new_light;

	new_light = gc_malloc(sizeof(t_light));
	if (!new_light)
		fatal_error(ERR_MEMORY, NULL);
	set_params(new_light);
	add_light(data->assets, new_light);
	return (1);
}
