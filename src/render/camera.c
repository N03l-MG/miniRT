/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmonzon <nmonzon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 17:16:05 by nmonzon           #+#    #+#             */
/*   Updated: 2025/03/14 17:45:01 by nmonzon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static t_vector calculate_pixel_position(t_camera *cam, float px, float py)
{
    t_vector pixel;
    float aspect_ratio = (float)WIDTH / (float)HEIGHT;
    float fov_adjustment = tan(cam->fov * M_PI / 360.0);
    float x_offset = (2 * ((px + 0.5) / WIDTH) - 1) * aspect_ratio * fov_adjustment;
    float y_offset = (1 - 2 * ((py + 0.5) / HEIGHT)) * fov_adjustment;
    
    // Create direction vector from camera orientation
    t_vector direction = vec_normalize(vec_new(cam->vec_x, cam->vec_y, cam->vec_z));
    t_vector up = vec_new(0, 1, 0);
    t_vector right = vec_normalize(vec_cross(direction, up));
    up = vec_cross(right, direction);

    // Combine the offset with the camera basis vectors
    pixel = vec_add(direction, 
            vec_add(vec_scale(right, x_offset), 
                   vec_scale(up, y_offset)));
    
    return vec_normalize(pixel);
}

void    camera_setup(t_camera *cam)
{
    // Normalize the camera's orientation vector
    t_vector direction = vec_normalize(vec_new(cam->vec_x, cam->vec_y, cam->vec_z));
    
    // Update camera's orientation vector with normalized values
    cam->vec_x = direction.x;
    cam->vec_y = direction.y;
    cam->vec_z = direction.z;
}

t_ray camera_ray_for_pixel(t_camera *cam, float px, float py)
{
    t_ray ray;
    
    ray.origin = vec_new(cam->pos_x, cam->pos_y, cam->pos_z);
    ray.direction = calculate_pixel_position(cam, px, py);
    
    return ray;
}

