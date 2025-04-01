/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmonzon <nmonzon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 12:30:38 by jgraf             #+#    #+#             */
/*   Updated: 2025/03/31 12:39:18 by nmonzon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "../MLX42/include/MLX42/MLX42.h"
# include "assets.h"
# include "color.h"

typedef enum e_log_type
{
	LOG,
	WARNING
}	t_log_type;

typedef enum e_error
{
	ERR_MEMORY,
	ERR_ARGS,
	ERR_FILE,
	ERR_WINDOW,
	ERR_IMAGE,
	ERR_DATA,
	ERR_AMBIENT,
	ERR_CAM,
	ERR_LIGHT,
	ERR_UNKNOWN
}	t_error;

typedef enum e_asset_type
{
	AST_LIGHT,
	AST_PLANE,
	AST_SPHERE,
	AST_CYLINDER,
	NO_TYPE
}	t_asset_type;

typedef struct s_window_data
{
	mlx_t			*mlx_window;
	mlx_image_t		*mlx_image;
	unsigned char	*image_data;
}	t_window_data;

typedef struct s_asset_node
{
	void				*asset_struct;
	t_asset_type		type;
	t_color				col;
	float				roughness;
	float				reflect;
	struct s_asset_node	*next;
}	t_asset_node;

typedef struct s_assets
{
	t_asset_node	*head;
	size_t			size;
	size_t			light_cnt;
	size_t			sphere_cnt;
	size_t			plane_cnt;
	size_t			cylinder_cnt;
}	t_assets;

typedef struct s_scene_data
{
	t_window_data	*window_data;
	t_ambient		*ambient;
	t_camera		*cam;
	t_assets		*assets;
	uint8_t			samples;
}				t_scene_data;

#endif
