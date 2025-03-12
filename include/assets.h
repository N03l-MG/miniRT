/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assets.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmonzon <nmonzon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:39:14 by nmonzon           #+#    #+#             */
/*   Updated: 2025/03/12 14:41:13 by nmonzon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASSETS_H
# define ASSETS_H

// Visual Assets
typedef struct s_ambient
{
	int	ratio;
	int	r;
	int	g;
	int	b;
}		t_ambient;

typedef struct s_camera
{
	int	x;
	int	y;
	int	z;
	int	vx;
	int	vy;
	int	vz;
	int	fov;
}		t_camera;

typedef struct s_light
{
	int	x;
	int	y;
	int	z;
	int	brightness;
}		t_light;


// Objects
typedef struct s_sphere
{
	struct s_sphere	*next;
	int				x;
	int				y;
	int				z;
	int				d;
	int				r;
	int				g;
	int				b;
}					t_sphere;

typedef struct s_plane
{
	struct s_plane	*next;
	int				x;
	int				y;
	int				z;
	int				vx;
	int				vy;
	int				vz;
	int				r;
	int				g;
	int				b;
}					t_plane;

typedef struct s_cylinder
{
	struct s_cylinder	*next;
	int					x;
	int					y;
	int					z;
	int					vx;
	int					vy;
	int					vz;
	int					d;
	int					h;
	int					r;
	int					g;
	int					b;
}						t_cylinder;

#endif
