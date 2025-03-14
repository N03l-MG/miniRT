/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmonzon <nmonzon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:07:12 by nmonzon           #+#    #+#             */
/*   Updated: 2025/03/14 17:37:13 by nmonzon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int    sphere_intersect(t_sphere *sphere, t_ray ray, double *t)
{
    t_vector    sphere_center;
    t_vector    oc;
    double      a;
    double      b;
    double      c;
    double      discriminant;
    float       radius;

    sphere_center = vec_new(sphere->pos_x, sphere->pos_y, sphere->pos_z);
    oc = vec_sub(ray.origin, sphere_center);
    radius = sphere->diameter / 2.0f;
    
    a = vec_dot(ray.direction, ray.direction);
    b = 2.0 * vec_dot(oc, ray.direction);
    c = vec_dot(oc, oc) - (radius * radius);
    discriminant = b * b - 4 * a * c;
    
    if (discriminant < 0)
        return (0);
    
    double t0 = (-b - sqrt(discriminant)) / (2.0 * a);
    double t1 = (-b + sqrt(discriminant)) / (2.0 * a);
    
    if (t0 > t1)
    {
        double tmp = t0;
        t0 = t1;
        t1 = tmp;
    }
    
    if (t0 < 0)
    {
        t0 = t1;
        if (t0 < 0)
            return (0);
    }
    
    *t = t0;
    return (1);
}

t_vector    sphere_normal(t_sphere *sphere, t_vector point)
{
    t_vector sphere_center;
    
    sphere_center = vec_new(sphere->pos_x, sphere->pos_y, sphere->pos_z);
    return vec_normalize(vec_sub(point, sphere_center));
}

