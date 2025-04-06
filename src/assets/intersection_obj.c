#include "miniRT.h"

static t_vector transform_point(t_vector p, t_obj *obj)
{
    // First apply inverse translation
    p.x -= obj->pos_x;
    p.y -= obj->pos_y;
    p.z -= obj->pos_z;
    
    // Then apply inverse rotation
    float rx = -obj->rot_x * M_PI / 180.0f;
    float ry = -obj->rot_y * M_PI / 180.0f;
    float rz = -obj->rot_z * M_PI / 180.0f;
    p = apply_rotation(p, rx, ry, rz);

    // Finally apply inverse scale
    if (obj->scale != 0.0f)
    {
        p.x /= obj->scale;
        p.y /= obj->scale;
        p.z /= obj->scale;
    }
    return p;
}

static bool triangle_intersect(t_vector v0, t_vector v1, t_vector v2, t_ray ray, double *t)
{
    t_vector edge1, edge2, h, s, q;
    float a, f, u, v;

    edge1 = vec_sub(v1, v0);
    edge2 = vec_sub(v2, v0);
    h = vec_cross(ray.direction, edge2);
    a = vec_dot(edge1, h);

    if (a > -0.00001 && a < 0.00001)
        return (false);

    f = 1.0 / a;
    s = vec_sub(ray.origin, v0);
    u = f * vec_dot(s, h);

    if (u < 0.0 || u > 1.0)
        return (false);

    q = vec_cross(s, edge1);
    v = f * vec_dot(ray.direction, q);

    if (v < 0.0 || u + v > 1.0)
        return (false);

    *t = f * vec_dot(edge2, q);
    return (*t > 0.00001);
}

bool obj_hit(t_obj *obj, t_ray ray, double *t)
{
    double min_t = INFINITY;
    bool hit = false;
    double temp_t;

    // Transform ray to object space
    ray.origin = transform_point(ray.origin, obj);
    
    // Transform ray direction with rotation and scale
    float rx = -obj->rot_x * M_PI / 180.0f;
    float ry = -obj->rot_y * M_PI / 180.0f;
    float rz = -obj->rot_z * M_PI / 180.0f;
    ray.direction = apply_rotation(ray.direction, rx, ry, rz);
    
    if (obj->scale != 0.0f)
    {
        ray.direction.x /= obj->scale;
        ray.direction.y /= obj->scale;
        ray.direction.z /= obj->scale;
        ray.direction = vec_normalize(ray.direction);
    }

    for (int i = 0; i < obj->num_faces; i++)
    {
        t_vector v0 = obj->vertices[obj->faces[i].v[0]];
        t_vector v1 = obj->vertices[obj->faces[i].v[1]];
        t_vector v2 = obj->vertices[obj->faces[i].v[2]];

        if (triangle_intersect(v0, v1, v2, ray, &temp_t))
        {
            if (temp_t < min_t)
            {
                min_t = temp_t;
                hit = true;
                obj->hit_face = i;
            }
        }
    }

    if (hit)
    {
        *t = min_t * obj->scale;  // Scale the intersection distance back to world space
    }
    return hit;
}

t_vector obj_normal(t_obj *obj, int face_index)
{
    t_vector normal;

    if (obj->num_normals > 0 && obj->faces[face_index].vn[0] >= 0)
    {
        normal = obj->normals[obj->faces[face_index].vn[0]];
    }
    else
    {
        t_vector v0 = obj->vertices[obj->faces[face_index].v[0]];
        t_vector v1 = obj->vertices[obj->faces[face_index].v[1]];
        t_vector v2 = obj->vertices[obj->faces[face_index].v[2]];

        t_vector edge1 = vec_sub(v1, v0);
        t_vector edge2 = vec_sub(v2, v0);
        normal = vec_normalize(vec_cross(edge1, edge2));
    }

    // Transform normal back to world space (only rotation needed for normals)
    normal = apply_rotation(normal, obj->rot_x * M_PI / 180.0f,
                          obj->rot_y * M_PI / 180.0f,
                          obj->rot_z * M_PI / 180.0f);
    return vec_normalize(normal);
}
