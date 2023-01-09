# OpenCL / OpenGL Particle System 

## Introduction
Particle systems are used in games, movies, etc. to depict phenomena such as clouds, dust, fireworks, fire, explosions, water flow, sand, insects, wildebeests, etc. Once you know what they are, you can't stop seeing them.

To make a particle system work, you manipulate a collection of many 3D particles to exhibit some behavior. ( Look here for more information.)

A bit of particle history: particle systems were first seen in the Star Trek II: The Wrath of Khan Genesis Demo. (Don't laugh -- that sequence was animated 40 years ago!)
In this project, you will use OpenCL and OpenGL together to make a cool particle system. (The degree of cool-ness is up to you.)

## Code snipet

The snipet code already does the following: (this is included here if you want to follow the logic)

Here are the structs that will hold particle positions and particle colors:

```
struct xyzw
{
	float x, y, z, w;
};

struct rgba
{
	float r, g, b, a;
};
```

Arrays of these structs will be created in GPU memory.

Why the .w and .a members of the structs? The .w is the homogeneous coordinate for positions. Most of the time it is 1.0, but it does have other uses. The .a is alpha, or transparency. It is not used here, but it could have been. So, those elements are here to allow for future expansion.

The velocities use the xyzw struct too, just for convenience.

## Requirements : 
Design your 3D environment. The particles need to start from somewhere. Where should that be? 
The particles need to start with initial velocities. What should those be?
Create an OpenGL buffer object to hold the particles' XYZW positions as an array-of-structures.
Create an OpenGL buffer object to hold the particles' RGBA colors as an array-of-structures.
Create a C++ array-of-structures to hold the particles' XYZ velocities.
(OpenGL buffer objects are used for position and color, but not velocity. 
```
This is because OpenGL will need to use positions and colors in the drawing, but not the velocities.)
```
Determine good starting values for the position, velocity, and color data structures.
For the position and color buffers, use glMapBuffer( ) to send the values directly to the GPU.
The velocity array is a C++ array-of-structures, so just fill it using C++ code.
```
glBindBuffer( GL_ARRAY_BUFFER, hPobj );
struct xyzw *points = (struct xyzw *) glMapBuffer( GL_ARRAY_BUFFER, GL_WRITE_ONLY );
for( int i = 0; i < NUM_PARTICLES; i++ )
{
	points[i].x = Ranf( XMIN, XMAX );
	points[i].y = Ranf( YMIN, YMAX );
	points[i].z = Ranf( ZMIN, ZMAX );
	points[i].w = 1.;
}
glUnmapBuffer( GL_ARRAY_BUFFER );
```
```
glBindBuffer( GL_ARRAY_BUFFER, hCobj );
struct rgba *colors = (struct rgba *) glMapBuffer( GL_ARRAY_BUFFER, GL_WRITE_ONLY );
for( int i = 0; i < NUM_PARTICLES; i++ )
{
	colors[i].r = Ranf( .3f, 1. );
	colors[i].g = Ranf( .3f, 1. );
	colors[i].b = Ranf( .3f, 1. );
	colors[i].a = 1.;
}
glUnmapBuffer( GL_ARRAY_BUFFER );


for( int i = 0; i < NUM_PARTICLES; i++ )
{
	hVel[i].x = Ranf( VMIN, VMAX );
	hVel[i].y = Ranf(   0., VMAX );
	hVel[i].z = Ranf( VMIN, VMAX );
}
```
Create two OpenCL buffers from the position and color OpenGL buffers using calls to clCreateFromGLBuffer( ). 
You don't need to transmit the data to these OpenCL buffers -- it is already there in the OpenGL buffers that they are now linked to.
For the velocity array, create an OpenCL buffer using clCreateBuffer and enqueue-transmit the C++ array-of-structures to it like you've done before using clEnqueueWriteBuffer( ).
Decide on a time step, DT. 
Your .cl program will need to know about it.
Create a .cl OpenCL kernel that will advance all of the particles by the timestep DT. The sample code shows giving the .cl program access to the particles' positions and velocities. You will need to use these, and will need to update them.
