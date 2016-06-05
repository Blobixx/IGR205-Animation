#ifndef movable_H
#define movable_H

#include <string>

#include "misc.hpp"

#define ROTATE_SLOWNESS 8
#define MOVE_INC  1.4f

using namespace std;

class movable
{
public:
	
	movable();
	movable(string name);
	virtual ~movable();

	void init();

	movable& operator= (const movable& other);

	virtual void draw();
	virtual void update();

	void move(int pitch, int turn, int roll, float x, float y, float z);

	void setName(string name);

	/// state variable
	matrix16f location, newLocation;

	string name;
};

#endif // movable_H
