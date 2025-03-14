/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assets.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmonzon <nmonzon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:39:14 by nmonzon           #+#    #+#             */
/*   Updated: 2025/03/14 16:21:10 by nmonzon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASSETS_H
# define ASSETS_H

// Visual Assets
typedef struct s_ambient
{
	float	ratio;
	int		col_r;
	int		col_g;
	int		col_b;
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
	int		col_r;
	int		col_g;
	int		col_b;
}	t_light;


// Objects
typedef struct s_sphere
{
	float	pos_x;
	float	pos_y;
	float	pos_z;
	float	diameter;
	int		col_r;
	int		col_g;
	int		col_b;
}	t_sphere;

typedef struct s_plane
{
	float	pos_x;
	float	pos_y;
	float	pos_z;
	float	vec_x;
	float	vec_y;
	float	vec_z;
	int		col_r;
	int		col_g;
	int		col_b;
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
	int		col_r;
	int		col_g;
	int		col_b;
}	t_cylinder;

#endif
