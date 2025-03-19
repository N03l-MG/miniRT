/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assets.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmonzon <nmonzon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:39:14 by nmonzon           #+#    #+#             */
/*   Updated: 2025/03/19 17:54:49 by nmonzon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASSETS_H
# define ASSETS_H

# include "color.h"

// Visual Assets
typedef struct s_ambient
{
	float	ratio;
	t_color	col;
}	t_ambient;

typedef struct s_camera
{
	float	pos_x;
	float	pos_y;
	float	pos_z;
	float	vec_x;
	float	vec_y;
	float	vec_z;
	float	fov;
}			t_camera;

typedef struct s_light
{
	float	pos_x;
	float	pos_y;
	float	pos_z;
	float	brightness;
	t_color	col;
}	t_light;


// Object Assets
typedef struct s_sphere
{
	float	pos_x;
	float	pos_y;
	float	pos_z;
	float	diameter;
	t_color	col;
}	t_sphere;

typedef struct s_plane
{
	float	pos_x;
	float	pos_y;
	float	pos_z;
	float	vec_x;
	float	vec_y;
	float	vec_z;
	t_color	col;
}	t_plane;

typedef struct s_cylinder
{
	float	pos_x;
	float	pos_y;
	float	pos_z;
	float	vec_x;
	float	vec_y;
	float	vec_z;
	float	diameter;
	float	height;
	t_color	col;
}	t_cylinder;

#endif
