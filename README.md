<div align="center">
  <h1>
    miniRT (42 project)
  </h1>
  <p>
    <b><i>Basic raytracing engine written in C using the MLX42 graphics library.</i></b>
  </p>
</div>

IMAGE

_This project was made in collaboration with [Cimex](https://github.com/Cimex404). He has uploaded it as his own repository as well!_

DESCRIPTION

## Features
- **Primitive Assets:**
	
- **Lighting:**
	
- **Roughness:**
	
- **Reflections:**
	
- **User Input:**
	
- **Quality Presets:**
	
- **Logging System:**
	

## Usage
To run miniRT on a scene you must use this command:

```bash
./miniRT "[scene file / path to scene file]"
```

The scene file must have the `.rt` extension and must follow a specific format:
- The scene _must_ include a single ambient light (`A`), a single camera (`C`) and a single point light (`L`).
- The **ambient light** parameters are `intensity` from 0 to 1 as a float and `color` in RGB format as three values from 0 to 255. _Color works this way for all assets._
- The **camera** parameters are `position` x,y,z `rotation` x,y,z as values from -1 to 1 and `focal length` or FOV as a value from 1 to 180.
- The **point light** parameters are `position` x,y,z as well as intensity and color in the same format as the ambient light.
- The scene can have any ammout of objects out of a selection of **planes** (`pl`), **spheres** (`sp`) and **cylinders** (`cy`).
- Planes extend infinitely and have a single normal that points in the direction of their rotation vector. They have `position` x,y,z `rotation` x,y,z and `color`.
- Spheres have `position` like all other objects, no rotation as it has no effect on the a sphere, `diameter` as a float and `color`, as per usual.
- Cylinders have `position` and `rotation` in the usual format as well as `diameter`, `height` and `color`.
- If any of these objects parameters is missing, in the wrong order or otherwise invalid the object will be ignored and not rendered. If the mandatory assets (ambient, camera and point light) are missing or invald the window will not launch at all.
- For all objects, in addition to their necessary parameters you can also add `roughness` and `reflectivity` as floats from 0 to 1 in that order. If not added, these parameters will default to some preset values.
- The parameters can be space-separated as much as you like and have any empty lines between assets. Any unrecognized assets will be ignored.
- You can also add commented lines to the scene file. To do this, simply add a `#` to the **start** of the line.

An example scene would look like this:
```rt
#AST  POSTION         ROTATION    LUM/FOV RAD HGT  COLOR       ROUGH REFLCT
A                                 0.1              240,255,255
C    -50,40.5,50      1,-0.25,-1  62
L    -5,10,60                     0.84             255,196,240

pl   0,-10,0          0,1,0                        0,255,0     0     0.4
pl   100,0,0          -1,0,0                       255,0,0     0     0
pl   0,0,-100         0,0,1                        0,0,255     0     0
sp   0,0,0                                20       255,0,255   0.8   0
sp   -10,20,0                             5        10,20,30    0     0.8
cy   10,40,-30        .5,1,.5             10 20    255,255,0
cy   50.0,7,-8        -1,0,1              20 15.5  0,255,255
sp   -5,0,-21                             16       255,255,255 0
```

**NOTE:** The project depends on my [libft](https://github.com/N03l-MG/libft) utilities library as well as [MLX42](https://github.com/codam-coding-college/MLX42) for graphics. Both are added as submodules in the repository.

## Future Plans

