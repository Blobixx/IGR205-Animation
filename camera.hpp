#ifndef camera_H
#define camera_H

#include "movable.hpp"
#include <string>

/// Hold location, orientation, and mode of the viewer
/**
	Also some experimental modes of movement 
	like following a given object, and following that
	objects every rotation, same with a delay, or just tracking
	the object without rotating with it.
  */
class camera:public movable
{
	public:

	camera();
	
	camera(string name);
	~camera();

	void init();

	void draw();

	void move(int pitch,int turn, int roll,float x, float y, float z);
	void look();

	float radius;	
};

#endif
