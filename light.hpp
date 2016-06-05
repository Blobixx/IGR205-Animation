#ifndef light_H
#define light_H

#include <GL/gl.h>

#include "camera.hpp"
#include "misc.hpp"


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
};


#endif

