/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ambience.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgraf <jgraf@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:56:11 by jgraf             #+#    #+#             */
/*   Updated: 2025/03/24 16:30:17 by jgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*	This is were we parse the input for the Ambient Light.
*	When there is an invalid number of splits for the corresponding section,
*	a fatal error is thrown as the ambient light can't be constructed, but the
*	program needs a properly constructed ambient light source.
*/

static void	check_valid(t_scene_data *data)
{
	if ((data->ambient->ratio < 0 || data->ambient->ratio > 1)
		|| (data->ambient->col.r < 0 || data->ambient->col.r > 255)
		|| (data->ambient->col.g < 0 || data->ambient->col.g > 255)
		|| (data->ambient->col.b < 0 || data->ambient->col.b > 255))
		fatal_error(ERR_DATA, NULL);
}

static void	set_params(t_ambient *ambient, char **param)
{
	ambient->ratio = ft_atof(param[1]);
	ambient->col.r = ft_atoi(get_split_param(param[2], 0));
	ambient->col.g = ft_atoi(get_split_param(param[2], 1));
	ambient->col.b = ft_atoi(get_split_param(param[2], 2));
}

void	parse_ambience(t_scene_data *data, char **param)
{
	if (get_number_of_split_elements(param) != 3)
		fatal_error(ERR_DATA, NULL);
	if (data->ambient == NULL)
		data->ambient = gc_malloc(sizeof(t_ambient));
	else
		printlog(LOG, "Ambient already exists... Replacing ambient.");
	if (get_number_of_splits(param[2], ',') != 3)
		fatal_error(ERR_DATA, NULL);
	set_params(data->ambient, param);
	check_valid(data);
	printlog(LOG, "Ambient Light setup successful.");
}
