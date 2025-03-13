/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assets.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmonzon <nmonzon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:39:14 by nmonzon           #+#    #+#             */
/*   Updated: 2025/03/13 16:37:55 by nmonzon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASSETS_H
# define ASSETS_H

// Visual Assets
typedef struct s_ambient
{
	float	ratio;
	int		r;
	int		g;
	int		b;
}	t_ambient;

typedef struct s_camera
{
	float	x;
	float	y;
	float	z;
	float	vx;
	float	vy;
	float	vz;
	float	fov;
}			t_camera;

typedef struct s_light
{
	float	x;
	float	y;
	float	z;
	float	brightness;
	int		r;
	int		g;
	int		b;
}	t_light;


// Objects
typedef struct s_sphere
{
	float	x;
	float	y;
	float	z;
	float	d;
	int		r;
	int		g;
	int		b;
}	t_sphere;

typedef struct s_plane
{
	float	x;
	float	y;
	float	z;
	float	vx;
	float	vy;
	float	vz;
	int		r;
	int		g;
	int		b;
}	t_plane;

typedef struct s_cylinder
{
	float	x;
	float	y;
	float	z;
	float	vx;
	float	vy;
	float	vz;
	float	d;
	float	h;
	int		r;
	int		g;
	int		b;
}	t_cylinder;

#endif
