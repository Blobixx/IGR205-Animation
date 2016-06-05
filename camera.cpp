#ifdef WIN32									
#include <windows.h>								
#endif										
#include <iostream>

#include <GL/gl.h>	
#include <GL/glu.h>	

#include "misc.hpp"
#include "movable.hpp"
#include "camera.hpp"

#include <cmath>
#ifdef WIN32
#define M_PI PI
#endif

camera::camera()
{
	init();
}

camera::camera(string name)
{
   	this->name = name;
	init();
}

camera::~camera()
{

}

void camera::init()
{
	radius = 10.0f;
}

void camera::draw()
{
}


void camera::move(int pitch, int turn, int roll, float x, float y, float z)
{
	vector3f temp;

		if (pitch != 0)
			location.RotateX(-pitch/ROTATE_SLOWNESS);
		
		if (turn != 0)
			location.RotateY(-turn/ROTATE_SLOWNESS);
		
		if (roll != 0)
			location.RotateZ(roll/ROTATE_SLOWNESS);
		
		location.Translate(x,y,z);
	
	newLocation = location;

}

void camera::look()
{
	
	gluLookAt( 
				//eye
				location.matrix[12],
				location.matrix[13],
				location.matrix[14], 

				// center
				location.matrix[12]+location.matrix[8],
				location.matrix[13]+location.matrix[9],
				location.matrix[14]+location.matrix[10], 

				// up
				location.matrix[4],
				location.matrix[5],
				location.matrix[6]);

	return;	
}
