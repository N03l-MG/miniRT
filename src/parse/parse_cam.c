/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cam.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgraf <jgraf@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:56:11 by jgraf             #+#    #+#             */
/*   Updated: 2025/03/14 08:14:22 by jgraf            ###   ########.fr       */
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
	if ((data->cam->fov < 0 || data->cam->fov > 180)
		|| (data->cam->vx < 0 || data->cam->vx > 1)
		|| (data->cam->vy < 0 || data->cam->vy > 1)
		|| (data->cam->vz < 0 || data->cam->vz > 1))
		fatal_error(ERR_DATA, NULL);
}

static void	set_params(t_camera *cam, char **param)
{
	cam->x = ft_atoi(get_split_param(param[1], 0));
	cam->y = ft_atoi(get_split_param(param[1], 1));
	cam->z = ft_atoi(get_split_param(param[1], 2));
	cam->vx = ft_atoi(get_split_param(param[2], 0));
	cam->vy = ft_atoi(get_split_param(param[2], 1));
	cam->vz = ft_atoi(get_split_param(param[2], 2));
	cam->fov = ft_atoi(param[3]);
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
