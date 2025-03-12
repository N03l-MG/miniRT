/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmonzon <nmonzon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 12:30:38 by jgraf             #+#    #+#             */
/*   Updated: 2025/03/12 15:07:36 by nmonzon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "../MLX42/include/MLX42/MLX42.h"
# include "assets.h"

typedef enum e_error
{
	ERR_MEMORY,
	ERR_ARGS,
	ERR_WINDOW,
	ERR_IMAGE,
	ERR_DATA
}	t_error;

typedef enum e_asset_type
{
	ASS_LIGHT,
	ASS_PLANE,
	ASS_SPHERE,
	ASS_CYLINDER
}	t_asset_type;

typedef struct s_window_data
{
	mlx_t			*mlx_window;
	mlx_image_t		*mlx_image;
	unsigned char	*image_data;
}	t_window_data;

typedef struct s_asset_node
{
	void			*asset_struct;
	struct s_asset	*next;
}	t_asset_node;

typedef struct s_assets
{
	t_asset_node	*head;
	t_asset_node	*tail;
	size_t			size;
}	t_assets;

typedef struct s_scene_data
{
	t_ambient	ambient;
	t_camera	cam;
	t_assets	*assets;
}				t_scene_data;

#endif