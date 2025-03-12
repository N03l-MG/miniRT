/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ambience.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgraf <jgraf@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:56:11 by jgraf             #+#    #+#             */
/*   Updated: 2025/03/12 17:12:28 by jgraf            ###   ########.fr       */
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
	if ((data->ambient->r < 0 || data->ambient->r > 255)
		|| (data->ambient->g < 0 || data->ambient->g > 255)
		|| (data->ambient->b < 0 || data->ambient->b > 255)
		|| (data->ambient->ratio < 0 || data->ambient->ratio > 1))
		error_fatal("Error! Parameters out of bounds for Ambient Light\n");
}

static void	set_params(t_ambient *ambient, char **param)
{
	ambient->ratio = ft_atof(param[1]);
	ambient->r = ft_atoi(get_split_param(param[2], 0));
	ambient->g = ft_atoi(get_split_param(param[2], 1));
	ambient->b = ft_atoi(get_split_param(param[2], 2));
}

void	parse_ambience(t_scene_data *data, char **param)
{
	if (get_number_of_split_elements(param) != 3)
		error_fatal("Error! Invalid config for Ambient Light\n");
	if (data->ambient == NULL)
		data->ambient = malloc(sizeof(t_ambient));
	if (get_number_of_splits(param[2], ',') != 3)
		error_fatal("Error! Invalid color for Ambient Light\n");
	set_params(data->ambient, param);
	check_valid(data);
}
