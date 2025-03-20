/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cam.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmonzon <nmonzon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:56:11 by jgraf             #+#    #+#             */
/*   Updated: 2025/03/20 16:07:38 by nmonzon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*	This is were we parse the input for the Camera.
*	When there is an invalid number of splits for the corresponding section,
*	a fatal error is thrown as the camera can't be constructed, but the
*	program needs a properly constructed camera.
*/

static void	check_valid(t_scene_data *data)
{
	if (data->cam->fov < 0 || data->cam->fov > 180)
		fatal_error(ERR_DATA, NULL);
	// Check if direction vector is zero
	if (data->cam->vec_x == 0 && data->cam->vec_y == 0 && data->cam->vec_z == 0)
		fatal_error(ERR_DATA, NULL);
}

static void	set_params(t_camera *cam, char **param)
{
	cam->pos_x = ft_atof(get_split_param(param[1], 0));
	cam->pos_y = ft_atof(get_split_param(param[1], 1));
	cam->pos_z = ft_atof(get_split_param(param[1], 2));
	cam->vec_x = ft_atof(get_split_param(param[2], 0));
	cam->vec_y = -ft_atof(get_split_param(param[2], 1));
	cam->vec_z = ft_atof(get_split_param(param[2], 2));
	cam->fov = ft_atof(param[3]);
}

void	parse_camera(t_scene_data *data, char **param)
{
	if (get_number_of_split_elements(param) != 4)
		fatal_error(ERR_DATA, NULL);
	if (data->cam == NULL)
		data->cam = gc_malloc(sizeof(t_camera));
	if (get_number_of_splits(param[1], ',') != 3)
		fatal_error(ERR_DATA, NULL);
	if (get_number_of_splits(param[2], ',') != 3)
		fatal_error(ERR_DATA, NULL);
	set_params(data->cam, param);
	check_valid(data);
	printlog(LOG, "Camera setup successful.");
}
