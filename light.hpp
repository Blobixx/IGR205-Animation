#ifndef light_H
#define light_H

#include <GL/gl.h>
//#include "objloader.hpp"
#include "camera.hpp"
#include "misc.hpp"
/// Simple light point source
/**
	
So far just hold the light color parameters and the location.

  Orientation is also stored even though a rotated point source
  is indistuinguishable from the non-rotated.

  There's also a visible .obj shell around the light in order to 
  make placement possible (rather than guessing the lights position
  by looking at it's effect on normal objects).

  There's no diminishment with distance, that would be interesting to
  implement and though I can think of at least one way to do it 
  (objects would be individually lit with a distance scaling factor,
  and perhaps the distance to the light would also have the object
  be split up for lighting in order to show a differential across
  it's surface), I'm curious what the conventional way is.

 */
class light:public movable
{
public:

	light();
	~light();

	light(camera *viewer,int number);

	void draw();

	// Keep track of where the camera is so bitmap can be oriented
	// properly.
	camera *viewer;  

	
	//objloader *lightobj;


	/** Currently lights aren't directional, so only keep a vector of
		 position and orientation doesn't matter.
		vector3f *position;
	*/
	GLfloat Ka[4];	// Ambient 
	GLfloat Kd[4];	// Diffuse
	GLfloat Ks[4]; // Specular

	/// From 0-7 (or how ever many lights can be handled at once).
	int GL_LIGHTX;
	
	/// Stdout toggle
	bool verbose;
};


#endif

