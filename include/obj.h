#ifndef OBJ_H
# define OBJ_H

# include "maths.h"
# include "color.h"

typedef struct	s_uv
{
	float	u;
	float	v;
}	t_uv;

typedef struct	s_face
{
	int	v[3];   // vertex indices
	int	vt[3];  // texture coordinate indices
	int	vn[3];  // normal indices
}	t_face;

typedef struct	s_obj
{
	t_vector	*vertices;
	t_vector	*normals;
	t_uv		*uvs;
	t_face		*faces;
	float		pos_x;
	float		pos_y;
	float		pos_z;
	float		vec_x;
	float		vec_y;
	float		vec_z;
	t_color		col;
	float		scale;
	float		roughness;
	float		reflect;
	int			num_vertices;
	int			num_normals;
	int			num_uvs;
	int			num_faces;
	int			hit_face;
}	t_obj;

#endif
