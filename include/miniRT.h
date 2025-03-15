/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmonzon <nmonzon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 11:05:08 by jgraf             #+#    #+#             */
/*   Updated: 2025/03/14 17:43:25 by nmonzon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

//	Libraries
# include "../libft/include/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"
# include "structs.h"
# include "maths.h"

//	Defines
# define	WIDTH 1080
# define	HEIGHT 720

//	Parsing
void		parse_elements(t_scene_data *data, int fd);
void		parse_ambience(t_scene_data *data, char **param);
void		parse_camera(t_scene_data *data, char **param);
int			parse_light(t_scene_data *data, char **param);
int			parse_sphere(t_scene_data *data, char **param);
int			parse_plane(t_scene_data *data, char **param);
int			parse_cylinder(t_scene_data *data, char **param);
void		free_split(char **splt);
char		*get_split_param(char *str, int i);
int			get_number_of_splits(char *str, char c);
int			get_number_of_split_elements(char **element);

//	Key Hooks
void		key_hook(mlx_key_data_t keydata, void* param);

//	Color
uint32_t	col_rgb(int r, int g, int b, int a);
int			get_r(uint32_t rgb);
int			get_g(uint32_t rgb);
int			get_b(uint32_t rgb);

//	Rendering
void		render_scene(t_scene_data *data);
void		draw_on_image(t_scene_data *data, mlx_image_t *img);
t_ray		camera_ray_for_pixel(t_camera *cam, float px, float py);
void		camera_setup(t_camera *cam);

// Shapes
bool		plane_intersect(t_plane *plane, t_ray ray, double *t);
bool		sphere_intersect(t_sphere *sphere, t_ray ray, double *t);
bool		cylinder_intersect(t_cylinder *cyl, t_ray ray, double *t);

//	Logging
void		printlog(t_log_type log_type, char *message);

//	Error Management
void		error(t_error error, char *context);
void		fatal_error(t_error error, t_window_data *window_data);
void		clean_exit(int status, t_window_data *window_data);

#endif
