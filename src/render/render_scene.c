/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmonzon <nmonzon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 17:45:06 by nmonzon           #+#    #+#             */
/*   Updated: 2025/03/14 17:22:28 by nmonzon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static uint32_t ray_color(t_scene_data *data, t_ray ray)
{
    t_asset_node *node;
    double closest_t = INFINITY;
    t_sphere *closest_sphere = NULL;
    double t;

    // Traverse the assets list looking for intersections
    node = data->assets->head;
    while (node)
    {
        if (node->type == ASS_SPHERE)
        {
            t_sphere *sphere = (t_sphere *)node->asset_struct;
            if (sphere_intersect(sphere, ray, &t) && t < closest_t)
            {
                closest_t = t;
                closest_sphere = sphere;
            }
        }
        node = node->next;
    }

    if (closest_sphere)
        return col_rgb(closest_sphere->col_r, closest_sphere->col_g, 
                      closest_sphere->col_b, 0xFF);
    
    // Background color (black)
    return col_rgb(0, 0, 0, 0xFF);
}

static void draw_on_image(t_scene_data *data, mlx_image_t *img)
{
    int i;
    int j;
    t_ray ray;

    // Setup camera orientation
    camera_setup(data->cam);

    i = 0;
    while (i < WIDTH)
    {
        j = 0;
        while (j < HEIGHT)
        {
            ray = camera_ray_for_pixel(data->cam, i, j);
            mlx_put_pixel(img, i, j, ray_color(data, ray));
            j++;
        }
        i++;
    }
}

void render_scene(t_scene_data *data)
{
    t_window_data window_data;

    (void)data;
    window_data.mlx_window = mlx_init(WIDTH, HEIGHT, "miniRT", false);
    if (!window_data.mlx_window)
        fatal_error(ERR_WINDOW, &window_data);
    window_data.mlx_image = mlx_new_image(window_data.mlx_window, 1280, 720);
    if (!window_data.mlx_image)
        fatal_error(ERR_IMAGE, &window_data);
    window_data.image_data = (unsigned char *)window_data.mlx_image->pixels;
    if (!window_data.image_data)
        fatal_error(ERR_DATA, &window_data);
    draw_on_image(data, window_data.mlx_image);
    mlx_image_to_window(window_data.mlx_window, window_data.mlx_image, 0, 0);
    mlx_key_hook(window_data.mlx_window, &escape_key, window_data.mlx_window);
    mlx_loop(window_data.mlx_window);
    clean_exit(EXIT_SUCCESS, &window_data);
}
