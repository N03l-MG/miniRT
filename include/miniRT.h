/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgraf <jgraf@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 11:05:08 by jgraf             #+#    #+#             */
/*   Updated: 2025/03/26 12:00:46 by jgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

			//   ~~    Includes   ~~    //
# include "../libft/include/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"
# include "structs.h"
# include "maths.h"
# include "render.h"

			//   ~~    Defines    ~~   //
// Standard quality
// # define WIDTH 800
// # define HEIGHT 500
// # define SHDW_SAMPLES 64
// # define MAX_REFLECT 50

// Low quality for smooth movement
// # define WIDTH 320
// # define HEIGHT 200
// # define SHDW_SAMPLES 1
// # define MAX_REFLECT 1

// High quality for nice screenshots
# define WIDTH 1600
# define HEIGHT 1000
# define SHDW_SAMPLES 80
# define MAX_REFLECT 100

# define DEFAULT_ROUGHNESS 0.6
# define DEFAULT_REFLECT 0.2
# define TOTAL_PIXELS (WIDTH * HEIGHT)

			//   ~~    Prototypes   ~~   //
//	Parsing
void		parse_elements(t_scene_data *data, int fd);
void		parse_ambience(t_scene_data *data, char **param);
void		parse_camera(t_scene_data *data, char **param);
int			parse_light(t_scene_data *data, char **param);
int			create_dark_light(t_scene_data *data);
int			parse_sphere(t_scene_data *data, char **param);
int			parse_plane(t_scene_data *data, char **param);
int			parse_cylinder(t_scene_data *data, char **param);
void		assign_properties(t_asset_node *current, void *asset, int type);
void		free_split(char **splt);
char		*get_split_param(char *str, int i);
int			get_number_of_splits(char *str, char c);
int			get_number_of_split_elements(char **element);

//	Key Hooks
void		key_hook(mlx_key_data_t keydata, void *param);
bool		translation_keys(mlx_key_data_t keydata, t_scene_data *data);
bool		rotation_keys(mlx_key_data_t keydata, t_scene_data *data);
bool		sample_keys(mlx_key_data_t keydata, t_scene_data *data);

//	Color
uint32_t	col_rgb(int r, int g, int b, int a);
uint32_t	merge_color(uint32_t col1, uint32_t col2, float val);
int			get_r(uint32_t rgb);
int			get_g(uint32_t rgb);
int			get_b(uint32_t rgb);

//	Rendering
void		render_scene(t_scene_data *data);
void		draw_frame(t_scene_data *data, mlx_image_t *img);
void		camera_setup(t_camera *cam);
t_ray		camera_ray_for_pixel(t_camera *cam, float px, float py);
uint32_t	trace_ray(t_scene_data *data, t_ray ray, int depth);
uint32_t	add_reflection(t_render *render, t_lighting lighting, int depth);
uint32_t	compute_color(t_lighting *lighting, t_render *render);
t_lighting	init_lighting(t_render *render);
float		calculate_diffuse(t_lighting *lighting);
float		calculate_specular(t_lighting *lighting, t_render *render);
t_vector	get_intersect(t_ray ray, double t);
t_light		*get_scene_light(t_scene_data *data);
t_vector	surface_normal(void *obj, t_vector point, t_asset_type type);
bool		is_occluded(t_scene_data *data, t_ray shadow_ray,
				float light_distance);
float		shadow_caster(t_scene_data *data, t_vector intersect,
				t_vector normal, t_light *light);
float		ambient_occlusion(t_scene_data *data, t_vector point,
				t_vector normal);

//	Shapes
bool		plane_hit(t_plane *plane, t_ray ray, double *t);
t_vector	plane_normal(t_plane *plane);
bool		sphere_hit(t_sphere *sphere, t_ray ray, double *t);
t_vector	sphere_normal(t_sphere *sphere, t_vector point);
bool		cylinder_hit(t_cylinder *cyl, t_ray ray, double *t);
bool		intersect_caps(t_cylinder *cyl, t_ray ray, double *t);
t_vector	cylinder_normal(t_cylinder *cyl, t_vector point);

//	Logging
void		printlog(t_log_type log_type, char *message);

//	Error Management
void		error(t_error error, char *context);
void		fatal_error(t_error error, t_window_data *window_data);
void		clean_exit(int status, t_window_data *window_data);

#endif
