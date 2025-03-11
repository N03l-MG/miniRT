/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmonzon <nmonzon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 12:30:38 by jgraf             #+#    #+#             */
/*   Updated: 2025/03/11 18:30:59 by nmonzon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "../MLX42/include/MLX42/MLX42.h"

typedef enum e_error
{
	ERR_MEMORY,
	ERR_ARGS,
	ERR_WINDOW,
	ERR_IMAGE,
	ERR_DATA
}	t_error;

typedef struct s_window_data
{
	mlx_t			*mlx_window;
	mlx_image_t		*mlx_image;
	unsigned char	*image_data;
}	t_window_data;

//	Visual element structs
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


//	Physical element structs
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


//	Data struct
typedef struct s_scene_data
{
	t_ambient	ambient;
	t_camera	cam;
	t_light		light;
	t_sphere	*shpere;
	t_plane		*plane;
	t_cylinder	*cylinder;
}				t_scene_data;

#endif